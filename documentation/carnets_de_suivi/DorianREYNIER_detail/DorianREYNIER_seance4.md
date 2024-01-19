*******************
# Compte rendu 
*******************
## Séance du 18 Janvier

  - ##### Présentation de mi-parcour
  Durant les 20 premières minutes nous avons préparé les montages des démonstatrions et nous sommes passés à la présentation.
 

  - ##### Connectique BlueTooth
   Avec Ludovic, nous avons connecter deux esclaves (module BlueTooth HC06) à un maître (module BlueTooth HC05), nous avons réussi à les appareillés ensembles mais nous n'avons pas pu les tester faute de port USB.

  - ##### Soudure
  Durant la majeure partie du cours j'ai fait de la soudure:  
  J'ai soudé quelques headers GPIO males sur des level shifter qui seront utiliser pour la communication entre la cartouche et la carte STM32 Nucléo car la STM ne délivre que du 3.3V alors que la cartouche communique en 6V.
  
  ![Header level shifter](/documentation/Images/headshifter.png)

  J'ai soudé des groupes de cable sur le port de la cartouche en respectant le schéma électrique donné sur le schéma ci-dessous.
  
  ![schéma electrique cartouche](/documentation/Images/schema_cartouche.png)
  ![soudure port cartouche](/documentation/Images/soudure_port_cartouche.png)

  J'ai soudé des cables sur les PCB des manettes pour pouvoir communiquer entre elle et l'arduino.
  ![soudure pcb manette](/documentation/Images/soudure_pcb_manette.png)
  
