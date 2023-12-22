*******************
# Compte rendu 
*******************

## Description

Console rétro NES (1987) de salon, émulée par Arduino, avec la particularité de pouvoir lire les cartouches originales. La Poly-NES accepte jusqu'à deux joueurs à l'aide de manettes sans fils.

## Séance du 13 Décembre

  - ##### Réalisation de la majorité du [dessin 3D du boitier de la Poly-nes](/boitier) sur le logiciel *onshape*
  Le boîtier de la console, dans lequel nous installerons par la suite tous les composants électroniques, est modélisé grâce à *onshape* dans le but de l'imprimer en 3D.
  
![nes3d](/documentation/Images/nes3d.png)
  
  - ##### Soudure des headers GPIO sur une carte arduino NANO
  Nous avons fait l'acquisition de deux cartes arduino NANO neuves afin de réaliser le circuit des manettes. Les cartes étant neuves, aucun GPIO n'était soudé
 dessus, j'ai donc dû le faire.
 
  Ayant quelques bases en soudage, j'ai aidé certains de mes camarades qui avaient des soudures à réaliser pour leur projet, tel que des moteurs.
  
![pinNanoD](/documentation/Images/pinNanoD.png)

 - ##### Anticipation de la prochaine séance

  Nous avons récupéré une carte arduino DUE, deux cartes arduino nano, deux paires de module Bluetooth (Maîtres et esclaves) pour commencer à étudier le fonctionnement de la communication entre deux arduinos grâce au BlueTooth ainsi que le code qui va avec.
  Indépendamment du Bluetooth, nous avons récupéré deux joysticks dans la même optique de se familiariser avec le composant.

## Séance du 21 Décembre


  - ##### Mise en place de la communication bluetooth
  Avec l'aide de M. Masson nous avons réussi à faire communiquer un module bluetooth maître avec son esclave.
  J'ai assisté Ludovic dans l'écriture du programme visant à transférer des octets au lieu de chaînes de caractères grâce aux modules bluetooth.
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
  

    
  - ##### Etablissement de la liste des éléments manquants à notre projet
  Nous nous sommes concertés pour mettre en commun le matériel manquant et ainsi le recupérer auprès du professeur ou lui demander de nous le commander.
  Nous avons cherché sur internet des références sur Amazon et AliExpress.
  
  On peut trouver une partie de la liste dans le [cahier des charges](/cahier_des_charges.md).

  - ##### Réalisation d'un croquis du [dessin 3D de la manette](/boitier/manette) sur le logiciel *onshape*
  Premier dessin de la manette pour l'imprimer en 3D pendant les vacances afin d'y faire rentrer la plaque de test ainsi que les composants électroniques.
  
![nes3d](/documentation/Images/nes3d2.png)

  
  - ##### Familiarisation avec la plaque de test
  J'ai commencé à faire un montage sur une plaque de test, sans souder, pour se rendre compte de l'espace nécessaire dans la manette. 
