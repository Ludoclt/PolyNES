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

 ![Test manette](/documentation/Images/montageTestManette.png)
  

    
  - ##### Etablissement de la liste des éléments manquants à notre projet
  Nous nous sommes concertés pour mettre en commun le matériel manquant et ainsi le recupérer auprès du professeur ou lui demander de nous le commander.
  Nous avons cherché sur internet des références sur Amazon et AliExpress.
  
  On peut trouver une partie de la liste dans le [cahier des charges](/cahier_des_charges.md).

  - ##### Réalisation d'un croquis du [dessin 3D de la manette](/boitier/manette) sur le logiciel *onshape*
  Premier dessin de la manette pour l'imprimer en 3D pendant les vacances afin d'y faire rentrer la plaque de test ainsi que les composants électroniques.
  
  ![nes3d2](/documentation/Images/nes3d2.png)

  
  - ##### Familiarisation avec la plaque de test
  J'ai commencé à faire un montage sur une plaque de test, sans souder, pour se rendre compte de l'espace nécessaire dans la manette. 

  ![Test montage plaque de test](/documentation/Images/premierMontagePlaqueTest.png)

  Les fils représentent juste une connection arduino-module, il manque également l'installation des leds ansi que de deux boutons.
  J'ai commencé à faire un montage sur une plaque de test, sans souder, pour se rendre compte de l'espace nécessaire dans la manette. 

  ## Séance du 11 Janvier

- ##### Soudure des headers GPIO sur une carte STM32
  La carte STM32 que nous avons pour le projet n'avait aucun header soudé dessus, j'ai donc soudé des headers femelles pour simplifier les prochains branchements tels que ceux du lecteur de cartouche.
  
  ![STM32_headers](/documentation/Images/STM32headers.png)
  
  Nous avons reçu les prises VGA commandées sur AliExpress. J'ai soudé les câbles dessus en respectant le schéma de montage sélectionné par Ludovic.
  
  ![VGA_V1](/documentation/Images/VGAV1.png)

  - ##### Test d'affichage
  Avec Ludovic, nous avons réalisé le montage de la prise VGA sur un arduino uno. Nous avons réussi à afficher le texte "TEST" sur le vidéo-projecteur de la salle.
  
  ![branchement_VGA_V1](/documentation/Images/branchementVGAV1.png)

  - ##### Conception de plaques de test
  Pour éviter la fabrication de PCB, j'ai réalisé deux plaques de tests contenant l'ensemble des boutons nécessaires à la manette: quatre en forme de croix pour la "croix directionnelle", deux centrés pour les boutons "Select" et "Start" et deux boutons jaunes pour les touches d'actions "A" et "B".\
  J'ai également retaillé les plaques pour qu'elle soit les plus petites possibles et prennent le moins de place dans le boîtier de la manette.
   
  ![Pcb_manette](/documentation/Images/pcbmanette.png)
  
- ##### Finalisation du [dessin 3D de la manette V2](/boitier/manettev2.stl) sur le logiciel *onshape*
  Amélioration des finitions et des détails de la manette, ajout de quatres trous pour insérer des leds pour créer un indicateur de batterie, ajout d'un emplacement pour un interrupteur d'allumage de la manette, création d'un emplacement pour une prise USB-C.
  
  ![manette_V2_3D](/documentation/Images/manettev23D.png)
    
  - ##### Test de taille du modèle 3D
  J'ai réalisé une première impression 3D de mauvaise qualité pour vérifier que la taille, la forme ainsi que l'emplacement des boutons et autres composants me conviennent.

  ![manette_V1](/documentation/Images/manetteV1.png)
  ![manette_V1_profil](/documentation/Images/manetteV1profil.png)
  
  Les modifications pour la V2 de la manette sont axées sur les deux boutons que j'avais oubliés au milieu de la manette (les boutons Start and Select). \
  Dans mon idée de faire un mélange entre une manette de N64 et une manette de NES, le placement des boutons A et B (les jaunes) n'était pas adapté donc je les ai mis en diagonale au lieu d'en ligne.\
  J'ai réimprimé la couche supérieure du modèle pour être sûr de ne pas faire d'erreur:

  ![manette_V2](/documentation/Images/manetteV2.png)

  Pour référence, voici une photo d'une manette de Nintendo 64, manette considérée comme une des pires manettes développées.
  ![manette_N64](/documentation/Images/manetteN64.png)
