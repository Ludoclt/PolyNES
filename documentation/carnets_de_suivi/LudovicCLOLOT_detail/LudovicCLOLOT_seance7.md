*******************
# Compte rendu 
*******************

## Séance du 12 Février

- ### Ecriture de la bibliothèque VGA
  Fin de l'écriture de la librairie STM32 qui va nous permettre d'avoir une sortie vidéo VGA pour la console, la bibliothèque peut être trouvée [ici](https://github.com/Ludoclt/vgaf4).  
  Ce qui a été fait en plus de la dernière fois est la configuration des timings pour le standard VGA (640x480), dont les valeurs sont répertoriées dans le tableau ci-dessous.  
  ![vga_timings](/documentation/Images/vga_timings.png).
  
  Les valeurs de timings sont renseignées dans des macros pour faciliter leurs utilisations:
  ```cpp
  #define WIDTH ((uint16_t)640)
  #define HEIGHT ((uint16_t)480)
  
  #define HSYNC ((uint16_t)96)
  #define HBP ((uint16_t)48)
  #define HFP ((uint16_t)16)
  
  #define VSYNC ((uint16_t)2)
  #define VBP ((uint16_t)33)
  #define VFP ((uint16_t)10)
  ```

  Voici le code qui permet donc la configuration des timings:
  ```cpp
  // timing setup
  LTDC->SSCR |= (((HSYNC - 1) << 16) | (VSYNC - 1));
  LTDC->BPCR |= (((HSYNC + HBP - 1) << 16) | (VSYNC + VBP - 1));
  LTDC->AWCR |= (((HSYNC + HBP + WIDTH - 1) << 16) | (VSYNC + VBP + HEIGHT - 1));
  LTDC->TWCR |= (((HSYNC + HBP + WIDTH + HFP - 1) << 16) | (VSYNC + VBP + HEIGHT + VFP - 1));
  // polarity
  LTDC->GCR &= ~(1 << 31); // HSYNC negative
  LTDC->GCR &= ~(1 << 30); // VSYNC negative
  ```
  Les valeurs écrites dans les registres du contrôleur LTDC respectent les indications de la [documentation](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf), où nous avons par exemple les infos à propos de la synchronisation verticale (VSYNC) et la synchronisation horizontale (HSYNC) renseignées dans le registre SSCR, et les infos à propos du back porch dans le registre BPCR.  
  ![ltdc_sscr](/documentation/Images/ltdc_sscr.png)  
  ![ltdc_bpcr](/documentation/Images/ltdc_bpcr.png)  

  Comme expliqué dans la doc, le stm32 nous permet d'avoir 3 couches graphiques (layers) qui vont venir se superposer pour former le rendu final.  
  ![ltdc_layers](/documentation/Images/ltdc_layers.png)  

  Pour nos besoin du projet, une seule layer suffit, on va donc configurer la layer2 à l'aide, encore, des registres:
  ```cpp
  // layer setup
  LTDC_Layer2->WHPCR |= (((HSYNC + HBP + WIDTH - 1) << 16) | (HSYNC + HBP));
  LTDC_Layer2->WVPCR |= (((VSYNC + VBP + HEIGHT - 1) << 16) | (VSYNC + VBP));

  LTDC_Layer2->CFBAR = (uint32_t)fb;

  LTDC_Layer2->CACR = 255;

  LTDC_Layer2->CFBLR |= (((WIDTH * PIXEL_SIZE) << 16) | (WIDTH * PIXEL_SIZE + 3));
  LTDC_Layer2->CFBLNR |= HEIGHT;

  // enable layer and LTDC activation
  LTDC_Layer2->CR |= LTDC_LxCR_LEN;
  LTDC->GCR |= LTDC_GCR_LTDCEN;
  ```
  Je vais passer les détails mais un registre ici nous intéresse car il est lié à un problème que nous allons rencontrer, il s'agit du registre CFBAR qui stock l'adresse mémoire qui pointe vers le premier pixel du framebuffer (liste d'entiers de 32 bits qui contient les pixels de l'écran), à une si haute resolution (640x480) stocker une telle liste prend beaucoup de place dans la RAM (640x480x32/8 = 1.17 Mo), la carte stm32 possède seulement 256 ko de ram donc elle ne peut même pas contenir le framebuffer.  
  Pour l'instant, celui-ci est stocké dans la mémoire flash en le déclarant comme une constante:
  ```cpp
  const uint32_t fb[WIDTH * HEIGHT] = {};
  ```
  Cela nous empêche de le modifier mais pour des tests de fonctionnement cela suffit.  
  Pour régler ce problème, il y a plusieurs voies, déjà, l'écran de la NES fait seulement 256x240 pixels, ce qui va nous permettre de réduire la taille du buffer mais pour cela il faut aussi ajuster les timings, on pourra le faire en vérifiant les valeurs à l'aide d'un oscilloscope.  
  Le deuxième moyen qui vient s'ajouter au premier est que le contrôleur LTDC possède une petite mémoire qui va nous permettre de stocker jusqu'à 256 couleurs différentes, le framebuffer contiendra alors seulement les indices qui vont permettre d'indexer cette mémoire, 256 couleurs sont suffisantes car la NES, elle, en possédait seulement 56.  

- ### Mise en place de la communication série via USART
  Comme nous avons abandonné l'Arduino IDE, nous avons plus accès à ses bibliothèques, il faut donc tout réecrire soi-même, pour pouvoir écrire des messages dans la console de l'ordinateur, il faut établir une communication série avec la carte ST-LINK intégrée sur la carte Nucleo, pour cela, on configure l'UART numéro 3 de la carte nucléo:
```cpp
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // enable USART3

GPIOD->MODER |= (0b10 << (8 << 1));
GPIOD->MODER |= (0b10 << (9 << 1));

GPIOD->OSPEEDR |= (0b11 << (8 << 1)) | (0b11 << (9 << 1));
GPIOD->AFR[1] |= (7 << (0 << 2)); // PD8 TX
GPIOD->AFR[1] |= (7 << (1 << 2)); // PD9 RX

USART3->BRR = (7 << 0) | (24 << 4); // Baud rate of 115200, PCLK1 at 45MHz
USART3->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
```
La valeur à écrire dans le registre BRR (registre qui contient la baud rate, ici 115200 bauds) peut être calculé à l'aide de la formule suivante:  
![baud_rate](/documentation/Images/baud_rate.png)  
![usart_brr](/documentation/Images/usart_brr.png)  

Ce code sera réutilisé pour configurer un autre usart qui va nous permettre de récupérer les données envoyés par l'ESP32-C3 qui fait office de module bluetooth pour connecter les manettes à la consoles.
