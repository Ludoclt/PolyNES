*******************
# Compte rendu 
*******************
## Séance du 21 Décembre


  - ##### Mise en place de la communication bleutooth
  Avec l'aide de M. Masson nous avons réussi à faire communiquer un module blootooth maître avec son esclave.
  J'ai assisté Ludovic dans l'écriture du programme visant à transférer des Octets aulieu de String grace au modules bluetooth.
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
  On peut trouver une partie de la liste dans le [cahier des charges](/cahier_des_charges.md).

  - ##### Réalisation d'un croquis du [dessin 3D de la manette](/boitier/manette) sur le logiciel *onshape*
  Premier dessin de la manette pour l'imprimer en 3D pendant les vacances afin d'y faire rentrer la plaque de test ainsi que les composants électroniques.
  
![nes3d](/documentation/Images/nes3d2.png)

  
  - ##### Soudure des headers GPIO sur une carte arduino NANO
  Nous avons fait l'acquisition de deux cartes arduino NANO neuves afin de réaliser le circuit des manettes. Les cartes étant neuves, aucun GPIO n'était soudé
 dessus, j'ai donc dû le faire.
 
  Ayant quelques bases en soudage, j'ai aidé certains de mes camarades qui avaient des soudures à réaliser pour leur projet, tel que des moteurs.
  
