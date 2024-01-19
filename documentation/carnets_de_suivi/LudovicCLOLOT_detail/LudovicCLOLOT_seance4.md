*******************
# Compte rendu 
*******************

## Séance du 18 Janvier

- ### Ecriture du code qui permet de communiquer avec la cartouche
  Ce code permet de récupérer les données du jeu en interfaçant la cartouche selon la [documentation](https://www.nesdev.org/wiki/Cartridge_connector).  
  Voici deux exemples de fonctions:
  ```cpp
  uint8_t readPRGByte(uint16_t addr)
  {
    LL_GPIO_WriteOutputPort(CPU_ADDR_PORT, addr);
    setCPUModeRead();
    setBusActive();
    delayMicroseconds(1);
    uint8_t data = LL_GPIO_ReadInputPort(CPU_DATA_PORT) & 0xFF;
    setBusInactive();
    return data;
  }
  
  void writePRGByte(uint16_t addr, uint8_t data)
  {
    LL_GPIO_WriteOutputPort(CPU_ADDR_PORT, addr);
    setCPUModeWrite();
    LL_GPIO_WriteOutputPort(CPU_DATA_PORT, data);
    setBusActive();
    delayMicroseconds(1);
    setBusInactive();
  }
  ```
  La fonction readPRGByte() va venir récupérer un octet sur la cartouche en mettant tous les pins d'adressage sur leurs états respectifs selon l'adresse passée en paramètre (nombre en 16 bits, 1 bit = 1 pin), suite à cela on lit le résultat sur les 8 pins de données qui correspondent à l'octet que l'on veut récupérer.  
  La fonction writePRGByte() fait sensiblement la même chose sauf qu'elle écrit sur les pins de données au lieu de les lire.  
  La cartouche est en mesure de savoir si on l'a lit ou on si l'écrit par le biais des fonctions setCPUModeRead() et setCPUModeWrite().  
  setBusActive() et setBusInactive() lance un cycle de lecture ou écriture.

  Pour pouvoir tester la récupération de données on utilise ce code dans la fonction loop:
  ```cpp
  if (Serial.available())
  {
    uint16_t addr = Serial.readString().toInt();
    if (addr >= 0x8000 && addr <= 0xFFFF)
    {
      Serial.print("Reading data at address : ");
      Serial.println(addr, HEX);
      Serial.print("Result : ");
      Serial.println(readPRGByte(addr), HEX);
    }
  }
  ```
  Ce code va nous permettre de récupérer des données en envoyant des adresses au hasard entrées dans le moniteur série comprises entre 0x8000 et 0xFFFF.

- ### Branchement et test de la cartouche
  Branchement de la cartouche à la carte stm32 suivant le schéma ci-dessous.  
  ![schema](/documentation/Images/schema_cartouche.png)  
  Les pins de la carte stm32 nucleo 144 fonctionnent par ports, chaque port contenant 16 pins, sauf que les pins sont dispersés sur la carte, ce qui produit un montage bordélique.  
  ![montage](/documentation/Images/montage_cartouche.png)  
  Ensuite, on teste le fonctionnement de la cartouche à des adresses au hasard:  
  ![test](/documentation/Images/test_cartouche.png)
