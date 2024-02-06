*******************
# Compte rendu 
*******************

## Séance du 5 Février

- ### Reception des composants commandés
  Nous avons reçu le matériel commandé avant les vacances de Noël, tel que les ports USB-C, les ports VGA et le connecteur de cartouche.

- ### Ecriture d'un driver LTDC pour écran TFT
  Pour des raisons techniques, on abandonne le framework Arduino pour utiliser le framework CMSIS (Common Microcontroller Software Interface Standard), cela nous permettra d'avoir plus de contrôles sur le microcontrôleur STM32F429.  
  L'inconvénient est qu'il faut réimplementer l'entièreté des fonctionnalités de base qui étaient fournies avec l'Arduino IDE, on commence donc avec l'écran, une interface optimisée pour contrôler efficacement les écrans LCD est fournie par le STM32, il s'agit du périphérique LTDC (LCD-TFT Display Controller), la documentation complète sur son fonctionnement peut être trouvée [ici](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf) au point 16.  
  Le but final du projet étant de pouvoir jouer à la NES sur un téléviseur, il est possible d'utiliser le contrôleur LTDC à cet effet en redirigeant les deux frequences de sorties HSYNC et VSYNC du contrôleur dans les entrées VGA respectives, pour les couleurs, ont peut utiliser le circuit ci-dessous pour convertir le format.  
  ![ltdc_block_diagram](/documentation/Images/ltdc_block_diagram.png)  
  ![circuit_vga_ltdc](/documentation/Images/vga_ltdc.png)
  
  Voici donc un aperçu du driver avec la fonction d'initialisation:
  ```cpp
  void LCD::clockInit()
  {
      RCC->APB2ENR |= RCC_APB2ENR_LTDCEN; // enable LTDC clock
  
      RCC->CR |= (1 << 16); // enable HSE
      while ((RCC->CR & (1 << 17)) == 0)
          ;
      FLASH->ACR |= FLASH_ACR_LATENCY_5WS; // flash memory delay
  
      // PLL clock configuration
      RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_0 | RCC_PLLCFGR_PLLM_3 | RCC_PLLCFGR_PLLM_4;
      RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_7 | RCC_PLLCFGR_PLLN_8;
      RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
  
      RCC->CR |= RCC_CR_PLLON; // enable PLL
      while (!(RCC->CR & RCC_CR_PLLRDY))
          ;
  
      RCC->CFGR |= RCC_CFGR_SW_PLL; // set PLL as source of the system frequency
      while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1)
          ;
  
      // PLLSAI (pixel clock) configuration
      RCC->PLLSAICFGR |= RCC_PLLSAICFGR_PLLSAIN_6 | RCC_PLLSAICFGR_PLLSAIN_7;
      RCC->PLLSAICFGR |= RCC_PLLSAICFGR_PLLSAIR_0 | RCC_PLLSAICFGR_PLLSAIR_2;
      RCC->DCKCFGR |= RCC_DCKCFGR_PLLSAIDIVR_0;
      RCC->DCKCFGR &= ~RCC_DCKCFGR_PLLSAIDIVR_1;
  
      RCC->CR |= RCC_CR_PLLSAION; // enable PLLSAI
      while (!(RCC->CR & RCC_CR_PLLSAIRDY))
          ;
  }
  ```
  Sur le processeur STM32, les périphériques sont par défaut éteint, il faut donc écrire donc les registres appropriés pour les allumer, notamment le registre RCC (Reset and Clock Control)  
  ![rcc_registry](/documentation/Images/rcc_registry.png)  
  Ensuite, nous devons configurer les différentes horloges qui vont être utilisées par le contrôleur LTDC, comme par exemple HSE à 25 mhz, détail du schéma des horloges ci-dessous  
  ![clock_tree](/documentation/Images/clock_tree.png)  

  On enchaine ensuite sur la configuration des ports (pins GPIO)  
  ```cpp
  void LCD::portSetup()
  {
      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
  
      GPIOE->MODER |= (2 << (4 << 1));
      GPIOE->AFR[0] &= ~GPIO_AFRL_AFRL4_0;
      GPIOE->AFR[0] |= GPIO_AFRL_AFRL4_1 | GPIO_AFRL_AFRL4_2 | GPIO_AFRL_AFRL4_3;

      ...
  
      GPIOK->MODER |= (1 << (3 << 1));
  }
  ```
  De même, on doit envoyer un signal d'horloge au périphérique en écrivant dans le registre RCC_AHB1ENR (les ports GPIO se trouvent sur le bus APB1) pour activer le port, ensuite, on écrit dans les registres appropriés pour définir le mode du pin (OUTPUT, Alternate Function, push-pull...), on peut lire le numéro de pin et le type de sortie dans le tableau ci-dessous, dans l'exemple du code il s'agit du pin PE4 qui correspond au bit 0 du bleu dans l'octet rgb (LCD_B0).  
  ![port_bit_config_table](/documentation/Images/port_bit_config_table.png)  
  ![alternate_function_mapping](/documentation/Images/alternate_function_mapping.png)  

  Suite à cela il faudra générer l'image en écrivant dans les registres appropriés et en respectant les timings adéquats.  
  ![timings_resolutions](/documentation/Images/timings_resolutions.png)  
  ![ltdc_timing_registers](/documentation/Images/ltdc_timing_registers.png)
