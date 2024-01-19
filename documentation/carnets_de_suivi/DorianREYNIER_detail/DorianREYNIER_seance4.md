*******************
# Compte rendu 
*******************
## Séance du 18 Janvier

  - ##### Présentation de mi parcours
  Durant les 20 premières minutes nous avons préparé les montages des démonstrations et nous sommes passés à la présentation.
 

  - ##### Connectique Bluetooth
   Avec Ludovic, nous avons connecté deux esclaves (module Bluetooth HC06) à un maître (module Bluetooth HC05), nous avons réussi à les appareiller ensemble mais nous n'avons pas pu les tester faute de port USB.

  - ##### Soudure
  Durant la majeure partie du cours j'ai fait de la soudure.
  J'ai soudé quelques headers GPIO mâles sur des level shifter qui seront utilisés pour la communication entre la cartouche et la carte STM32 nucléo car la STM ne délivre que du 3.3V alors que la cartouche communique en 6V.
  
  ![Header level shifter](/documentation/Images/headshifter.png)

  J'ai soudé des groupes de câbles sur le port de la cartouche en respectant le schéma électrique donné sur le schéma ci-dessous.
  
  ![schéma electrique cartouche](/documentation/Images/schema_cartouche.png)
  ![soudure port cartouche](/documentation/Images/soudure_port_cartouche.png)

  J'ai soudé des cables sur les PCB des manettes pour qu'elle puisse communiquer avec l'arduino.
  
  ![soudure pcb manette](/documentation/Images/soudure_pcb_manette.png)


  - ##### Gestion du hardware
  La manette étant trop épaisse nous cherchons un agencement prenant moins de place pour essayer de réduire la hauteur de cette dernière.
  Nous sommes arrivés à la conclusion que remplacer l'arduino nano et le module HC06 par un XIAO esp32-s3, nous permetrait de gagner 50 millimètres de      
  hauteur.

  ![agencement V1](/documentation/Images/agencementV1.png)
