*******************
# Compte rendu 
*******************

## Présentation du projet

Console rétro NES (1987) de salon, émulée par Arduino, avec la particularité de pouvoir lire les cartouches originales. La Poly-NES accepte jusqu'à deux joueurs à l'aide de manettes sans fils.

## Séance du 14 Décembre

- ### Début de l'écriture du code de l'émulateur

  Début de l'implémentation du CPU de la console, qui consiste à réimplémenter tous les modes d'adressages et les 56 différentes instructions du processeur [6502](https://fr.wikipedia.org/wiki/MOS_Technology_6502), et de reproduire son comportement.
   
  Voici quelques exemples d'implémentations:
  
  ```cpp
  // Adressing Modes
  
  uint8_t CPU::ZPY()
  {
      absAddr = bus->read(pc) + yReg;
      pc++;
      absAddr &= 0x00FF;
      return 0;
  }
  
  uint8_t CPU::ABX()
  {
      uint16_t lo = bus->read(pc);
      pc++;
      uint16_t hi = bus->read(pc);
      pc++;
      absAddr = (hi << 8) | lo;
      absAddr += xReg;
      return (absAddr & 0xFF00) != hi << 8 ? 1 : 0;
  }
  
  uint8_t CPU::IND()
  {
      uint16_t ptr_lo = bus->read(pc);
      pc++;
      uint16_t ptr_hi = bus->read(pc);
      pc++;
      uint16_t ptr = (ptr_hi << 8) | ptr_lo;
      absAddr = (bus->read(ptr + 1) << 8) | bus->read(ptr + 0);
      return 0;
  }

  // Instructions
  
  // Arithmetic
  
  uint8_t CPU::ADC()
  {
      fetchData();
      uint16_t result = (uint16_t)accu + (uint16_t)data + (uint16_t)getFlag(C);
      setFlag(C, result > 255);
      setFlag(Z, (result & 0x00FF) == 0);
      setFlag(N, result & 0x80);
      setFlag(V, (~((uint16_t)accu ^ (uint16_t)data) & ((uint16_t)accu ^ (uint16_t)result)) & 0x0080);
      accu = result & 0x00FF;
      return 1;
  }
  
  // Increment and Decrement
  
  uint8_t CPU::INC()
  {
      fetchData();
      data++;
      setFlag(N, data & 0x80);
      setFlag(Z, data == 0x00);
      bus->write(absAddr, data);
      return 0;
  }
  
  // Shift and Rotate
  
  uint8_t CPU::ROL()
  {
      fetchData();
      setFlag(C, data & 0x80);
      uint8_t result = (data << 1) | getFlag(C);
      setFlag(N, result & 0x80);
      setFlag(Z, result == 0x00);
      if (instructions[opcode].addrmode == &CPU::IMP)
          accu = result;
      else
          bus->write(absAddr, result);
      return 0;
  }
  ```
  Pour plus d'informations, voir [ici](https://en.wikibooks.org/wiki/6502_Assembly).

- ### Etude du circuit d'une cartouche NES
  Afin de pouvoir mettre en place une communication entre le système émulé et la cartouche physique, il faut identifier les composants environnants celle-ci ainsi que les pins nécessaires pour mettre en place la communication.
  ![diagram](/documentation/Images/cartridge_diagram.png)

- ### Etude des différents modules de communication sans fil
  Pour pouvoir établir une communication entre les manettes sans fil et la console, il a fallu étudier différents modules comme le module RF HC-12 ou bien les modules Bluetooth HC-05 et HC-06 afin de déterminer quelle solution est la plus adaptée pour, en l'occurrence, avoir un seul module maitre connecté à deux modules esclaves.  
  J'ai par ailleurs aidé des collègues d'un autre groupe à configurer et mettre en place une communication entre deux modules HC-12.

- ### Divers
  Soudure de headers GPIO sur un arduino nano.  
  Récupération de matériel.

## Séance du 21 Décembre

- ### Début de l'écriture du code des manettes
  Début de l'écriture du code qui permet d'établir la communication entre la carte principale et les manettes, pour l'instant le maitre HC-05 communique avec seulement un esclave HC-06 et l'état des boutons est affiché dans le moniteur série.  
  exemple avec le code de l'esclave:
  ```cpp
  #include <SoftwareSerial.h>

  #define RX 11
  #define TX 12
  
  #define BUTTON_A 3
  #define BUTTON_B 2
  
  struct ControllerData
  {
    bool A;
    bool B;
  };
  ControllerData data;
  ControllerData lastData;
  
  SoftwareSerial BlueT(RX,TX);
  
  void setup(){
    Serial.begin(9600);
    BlueT.begin(38400);
  
    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
  
    data = (ControllerData) {false, false};
    lastData = data;
  }
  
  void loop(){
    data.A = !digitalRead(BUTTON_A);
    data.B = !digitalRead(BUTTON_B);
    if (memcmp(&data, &lastData, sizeof(ControllerData))) {
      BlueT.write((byte *)&data, sizeof(ControllerData));
      Serial.println("A : " + String(data.A) + " B : " + String(data.B));
      lastData = data;
    }
  }
  ```

- ### Divers
  Aide à un collègue sur l'utilisation d'un écran lcd.  
  Récupération du matériel nécessaire à la lecture des cartouches (plus grosse carte, shift registers...).

## Séance du 11 Janvier

- ### Début de l'écriture du code qui permet de récupérer les données de la cartouche
  Cette ébauche de code permet de récupérer un octet du programme du jeu à l'adresse spécifiée.

- ### Branchement de l'écran et de l'adaptateur microSD à l'Arduino Due
  En attendant d'avoir un lecteur de cartouches et une sortie vidéo VGA complètement fonctionnelle, on utilisera un écran TFT LCD ainsi qu'une carte microSD dans laquelle seront sauvegardé les jeux pour effectuer des tests.
  ![due-tft-sd](/documentation/Images/due-tft-sd.png)

- ### Test de l'adaptateur microSD
  Test de la carte microSD en affichant les caractéristiques et les fichiers présents dessus.
  ![test-sd](/documentation/Images/test-sd.png)

- ### Test de l'écran TFT
  Test de l'écran TFT en y affichant des formes arbitraires.
  ![test-tft](/documentation/Images/test-tft.png)

- ### Montage de la prise VGA
  ![schema-vga](/documentation/Images/schema-vga.png)  
  Réalisation du montage avec Dorian de la prise VGA en respectant le schéma ci-dessus, ce montage permet seulement d'afficher de la vidéo monochrome, il faudra donc le modifier à l'avenir, de même pour la bibliothèque VGA trouvée sur internet.
  ![branchementVGAV1](/documentation/Images/branchementVGAV1.png)

- ### Test de l'affichage VGA
  Nous avons testé l'affichage VGA avec Dorian à la fin de la séance en affichant simplement le mot "TEST" sur le vidéoprojecteur.

- ### Divers
  Aide à un collègue sur la mise en place d'une communication entre deux modules HC-12.
