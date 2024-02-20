*******************
# Compte rendu 
*******************

## Séance du 19 Février

- ### Résolution de problèmes
  On a cherché avec Dorian l'origine du problème de la manette qui faisait qu'elle ne détectait pas l'état des boutons.

- ### Outils de débuggage
  Réimplementation de certains outils tels que la fonction println afin de faciliter le débuggage du programme, cela utilise la communication USART établie la dernière fois.
  ```cpp
  void sendChar(char c)
  {
      while ((USART3->SR & USART_SR_TXE) == 0)
          ;
      USART3->DR = c;
  }
  
  void sendString(const char *s)
  {
      while (*s)
      {
          sendChar(*s++);
      }
  }
  
  void sendInt(int number)
  {
      char buf[4];
      sprintf(buf, "%d", number);
      sendString(buf);
  }
  
  void print(const char *s, ...)
  {
      va_list args;
      va_start(args, s);
  
      while (*s)
      {
          if (*s == '%')
          {
              switch (*(++s))
              {
              case 's':
                  sendString(va_arg(args, const char *));
                  break;
              case 'd':
                  sendInt(va_arg(args, int));
                  break;
              default:
                  sendChar(*s);
                  break;
              }
              s++;
          }
          else
              sendChar(*s++);
      }
      va_end(args);
  }
  
  void println(const char *s, ...)
  {
      print(s);
      sendChar('\n');
  }
  ```

- ### Réimplementation delay
  Comme pour les fonctions de print, il faut réimplementer la fonction delay, pour cela, on utilise le SysTick qui est un timer commun aux processeurs ARM Cortex-M4, dont la documentation peut être trouvée [ici](https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf). Comme on a besoin d'un décompte qui tourne en parallèle du programme principal pour certains besoins tels que la lecture de carte sd, il faut utiliser un interrupt.
  ```cpp
  void SysTick_Handler(void)
  {
      if (elapsed_time != counter_time)
          elapsed_time++;
      else
      {
          // stop counter
          SysTick->CTRL &= ~1;        // disable SysTick
          SysTick->CTRL &= ~(1 << 1); // disable interrupt
          elapsed_time = 0;
          counter_time = 0;
          isr_delay = 0;
      }
      if (isr_delay != 0)
          isr_delay--;
  }
  
  void sysTickInit(uint32_t ahb_freq)
  {
      // reset CTRL
      SysTick->CTRL &= ~(0b111 | (1 << 16));
      // set AHB clock as SysTick source
      SysTick->CTRL |= (1 << 2);
      // set reload value for 1 ms tick
      SysTick->LOAD = ahb_freq / 1000 - 1;
  }
  
  void delay_ms(uint32_t ms)
  {
      if (counter_time == 0)
      {
          SysTick->VAL = 0;   // set current value to 0
          SysTick->CTRL |= 1; // enable SysTick
          while (ms)
          {
              while ((SysTick->CTRL & (1 << 16)) == 0)
                  ;
              ms--;
          }
          SysTick->CTRL &= ~1; // disable SysTick
      }
      else
      {
          isr_delay = ms;
          while (isr_delay != 0)
              ;
      }
  }
  
  void beginCounter(uint32_t ms)
  {
      counter_time = ms;
      SysTick->VAL = 0;          // set current value to 0
      SysTick->CTRL |= (1 << 1); // enable interrupt
      SysTick->CTRL |= 1;        // enable SysTick
  }
  
  uint32_t getElapsedTime(void)
  {
      return elapsed_time;
  }
  
  uint8_t isTimeElapsed(void)
  {
      return counter_time == 0 ? 1 : 0;
  }
  ```

- ### Port de la bibliothèque FatFs
  Nous avons besoin de pouvoir lire des fichiers sur une carte sd à l'aide du protocole SDIO afin de pouvoir jouer à des jeux stockés sur la carte, pour faire cela correctement et interagir avec le système de fichiers, il faut porter la librairie [FatFs](http://elm-chan.org/fsw/ff/) sur stm32 en implémentant les fonctions spécifiques à la platforme telle que l'écriture ou la lecture du disque, voici un exemple avec la fonction send_cmd:
  ```cpp
  static int send_cmd(WORD idx, DWORD arg, int resp_type, DWORD *buf)
  {
  	DWORD cmd;
  	DWORD s;
  
  	lib_delay_ms(1);
  
  	if (idx & 0x80)
  	{ /* ACMD class */
  		if (!send_cmd(55, ((DWORD)card_rca) << 16, RESP_SHORT, buf) || !(buf[0] & 0x00000020))
  			return 0;
  	}
  
  	idx &= 0x3F;
  	SDIO->ICR = 0xc007ff;
  
  	SDIO->ARG = arg;
  
  	cmd = (1 << 10) | idx;
  	if (resp_type == RESP_SHORT)
  		cmd |= (1 << 6);
  	else if (resp_type == RESP_LONG)
  		cmd |= (1 << 6) | (1 << 7);
  
  	SDIO->CMD = cmd;
  	lib_beginCounter(100);
  
  	while (1)
  	{
  
  		if (lib_isTimeElapsed())
  		{
  			break;
  		}
  
  		s = SDIO->STA;
  		if (resp_type == RESP_NONE)
  			return s & (1 << 7) ? 1 : 0;
  		else
  		{
  			/* check if timeout */
  			if (s & (1 << 3))
  			{
  				lib_println("Error ! %s timeout idx=%d arg=%d", __func__, (uint32_t)idx, (uint32_t)arg);
  				return 0;
  			}
  
  			/* check if crc err */
  			if (s & (1 << 1))
  			{
  				if (idx == 1 || idx == 12 || idx == 41)
  					break;
  				lib_println("Error ! %s crcfail idx=%d arg=%d", __func__, (uint32_t)idx, (uint32_t)arg);
  				return 0;
  			}
  
  			if (s & (1 << 6))
  				break;
  		}
  	}
  
  	buf[0] = SDIO->RESP1;
  	if (resp_type == RESP_LONG)
  	{
  		buf[1] = SDIO->RESP2;
  		buf[2] = SDIO->RESP3;
  		buf[3] = SDIO->RESP4;
  	}
  
  	return 1;
  }
  ```

- ### Test VGA
  Après récupération de l'adaptateur VGA soudé par Dorian, je l'ai testé et les tests ont été concluants, il y a quelques ajustements à faire notamment sur le fait qu'un pin de données de la composante rouge est absent de la carte stm32 nucleo 144, on peut pallier ce manque en connectant le pin manquant (R1) à un autre pin de la composante rouge par exemple R3, mais cela réduit les nuances de rouge qu'il est possible d'obtenir, il va donc falloir adapter la palette. L'autre ajustement est qu'il faut rajouter une résistance entre la sortie et l'entrée HSYNC/VSYNC de la carte et de l'adaptateur VGA pour s'assurer que les impulsions rapides seront transmises correctement. Des optimisations de mémoire sont également à prévoir.  
  La prochaine étape est donc le montage final avec l'intégration de l'émulateur dans le code.
