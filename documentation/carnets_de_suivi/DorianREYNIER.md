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

## Séance du 18 Janvier

  - ##### Présentation de mi parcours
  Durant les 20 premières minutes nous avons préparé les montages des démonstrations et nous sommes passés à la présentation.
 

  - ##### Connectique Bluetooth
  Avec Ludovic, nous avons connecté deux esclaves (module Bluetooth HC06) à un maître (module Bluetooth HC05), nous avons réussi à les appareiller ensemble     mais nous n'avons pas pu les tester faute de port USB.

  - ##### Soudure
  Durant la majeure partie du cours j'ai fait de la soudure.
  J'ai soudé quelques headers GPIO mâles sur des level shifter qui seront utilisés pour la communication entre la cartouche et la carte STM32 nucléo car la 
  STM ne délivre que du 3.3V alors que la cartouche communique en 5V.
  
  ![Header level shifter](/documentation/Images/headshifter.png)

  J'ai soudé des groupes de câbles sur le port de la cartouche en respectant le schéma électrique donné sur le schéma ci-dessous.
  
  ![schéma electrique cartouche](/documentation/Images/schema_cartouche.png)
  ![soudure port cartouche](/documentation/Images/soudure_port_cartouche.png)

  J'ai soudé des câbles sur les PCB des manettes pour qu'elles puissent communiquer avec l'arduino.
  
  ![soudure pcb manette](/documentation/Images/soudure_pcb_manette.png)


  - ##### Gestion du hardware
  La manette étant trop épaisse nous cherchons un agencement prenant moins de place pour essayer de réduire la hauteur de cette dernière.
  Nous sommes arrivés à la conclusion que remplacer l'arduino nano et le module HC06 par un XIAO esp32-s3 nous permetrait de gagner 50 millimètres de      
  hauteur.

  ![agencement V1](/documentation/Images/agencementV1.png)
## Séance du 18 Janvier

- ##### Soudure
  Nous avons récupéré du matériel pour avancer dans le projet:  
    
  j'ai soudé quelques des GPIO mâles sur de nouveaux level shifter fournis par le professeur ainsi que sur deux ESP32-C3 que M. Masson nous fournit en       
  remplacement des XIAO ESP32-S3.
  
  ![Header level shifter](/documentation/Images/headshifter2.png)
  ![ESP32-C3](/documentation/Images/ESP32-C3.png)

  J'ai soudé pas mal de matériel pour d'autres groupes tel que des moteurs, des GPIO, des câbles...
    
  ![soudure moteur](/documentation/Images/soudure_moteur.png)

  Ludovic m'avait donné des Shift register 74CH595 (Shift register SIPO), en me renseignant j'ai découvert la distinction entre un Shift register SIPO et un     Shift register PISO.  
  En expliquant mes nécessités à M. Juan il m'a trouvé des Shift register PISO (SN74LS165AN)

  ![Shift Register](/documentation/Images/Shift_Register.png)

  J'ai d'abord essayé le Shift register avec un bouton sur une arduino nano, le montage réussi, j'ai reproduit le montage sur un ESP32-C3, mais il n'a          fonctionné tout de suite. En cherchant j'ai découvert que la connexion est désactivée de base sur ces ESP32-C3, après réactivation dans l'onglet outil de    l'IDE Arduino, tout a fonctionné comme souhaité.

  ![Montage Shift Register](/documentation/Images/Montage_Shift_Register.png)
  ![Test Shift Register](/documentation/Images/tst_shift_registers.png)
```cpp
// code pour tester registre à décalage
//PL pin1
int load = 7;

//CE pin 15
int clockEnablePin = 4;

//Q7 pin 7
int dataIn = 5;

//CP pin2
int clockIn = 6;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(load, OUTPUT);
pinMode(clockEnablePin, OUTPUT);
pinMode(clockIn, OUTPUT);
pinMode(dataIn, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(load, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  delayMicroseconds(5);

  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnablePin, LOW);
  byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin, HIGH);
  Serial.print("Pin States:\r\n");
  Serial.println(incoming, BIN);
  delay(200);

}
```
  
  
- ##### Connectique Bluetooth
  Pendant la fin du cours, j'ai commencé les recherches pour mettre en place un connexion bluetooth entre les ESP32-C3, un agissant comme un serveur et     l'autre comme un client.

Une fois le problème du bluetooth résolue il ne restera plus que le montage final des manettes.

## Séance du 5 Févirer

- ##### Réception des composants commandés
  Nous avons reç le materiel commandé avant les vacances de noël tel que des ports USB C, des boutons avec embouts de couleurs, un joystick...  
  J'ai également recupérer un troisième esp32 C3  
 
  ![USBC](/documentation/Images/USBC.png)


- ##### Soudure
 
  Comme à chaque fois l'esp32 était neuf, jai donc soudé les GPIO mâles dessus. Un camarade m'a demandé de lui soudé les siens, ce que j'ai fait.       

  ![ESP32-C3_2](/documentation/Images/ESP32-C3_2.png)

  Les tests du Shift register étant concluants, j'ai installé le composant sur ma plaque d'essai et j'y ai soudé les bouttons.  
  j'ai du souder des resistances sur les bouton car l'usage du pullup est impossible combiné avec un Shift register.  
  ![pcb_recto](/documentation/Images/pcb_recto.png)    
  ![pcb_verso](/documentation/Images/pcb_verso.png)
  
- ##### Connectique Bluetooth
  J'ai également reussi à établir la connection Bluetooth entre deux esp32 (un serveur et un client) grâce aux codes exemples fourni dans la bibliotheque BLE.
  Pour la prochaine scéance, je fais tester ce même pour faire communiquer deux client avec le serveur.
  
## Séance du 12 Févirer

- ##### Modification du cahier des charges
  Après installation, nous nous sommes rendu compte que l'ajout d'un joystick était inutile. En effet le joystick étant digital et la nes comprenant le numérique, le joystick est injouable (il faut aller tout au bout de la course pour qu'il soit détecté). Ne représentant pas de déft technique (lecture de deux potentiomètres), nous avons pris la décision de le retirer.  
  Ce retrait implique une retouche sur le modèle 3D pour retirer son logement [dessin 3D de la manette sans joystick](/boitier/manettev3.stl).
 
  ![Manette V3](/documentation/Images/Manette_V3.png)


- ##### Soudure
 
  J'ai trouvé un montage plus efficace pour les pcb des manettes, j'ai donc dû désouder tous les fils et refaire le montage du début.    

  ![PCB V2](/documentation/Images/pcbV2.png)

    J'ai également commencé à faire une carte vidéo pour transformer la sortie de huit sorties par composantes vers une sortie par composante pour le vga
  
  ![PCB video](/documentation/Images/pcb_video.png)

  Comme à mon habitude j'ai soudé des câbles sur des moteurs ainsi que des boutons et des headers sur des modules divers pour les autres groupes.

- ##### Impression 3D
  Durant le week end ainsi que la JPO, j'ai demandé à M.Jaun d'imprimer le boitier de la console.  
  Le boitier ayant une face de 256 mm, une seule imprimante avait un plateau suffisamment grand, le problème est que cette imprimante à nombreuses difficultés, l'impression a échoué 4 fois. J'ai donc dû refaire le [boitier](/boitier/boitier_mini.stl) pour le faire rentrer sur le plateau des prusa mk4 (25cm max).  
  À cause des nombreux détails ainsi que la structure, il le remodelage du modèle était aussi long de sa conception.
  
  ![boitier 3D mini](/documentation/Images/boitier_3D_mini.png)
