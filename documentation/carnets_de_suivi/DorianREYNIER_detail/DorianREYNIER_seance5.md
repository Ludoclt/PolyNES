*******************
# Compte rendu 
*******************
## Séance du 18 Janvier

- ##### Soudure
  Nous avons recupéré du materiel pour avancer dans le projet:
  
  J'ai soudé quelques des GPIO mâles sur de nouveaux level shifter fournis par le professeur.
  
  ![Header level shifter](/documentation/Images/headshifter2.png)

  J'ai soudé pas mal de materiel pour d'autre groupes tel que des moteurs, des GPIO, des câbles...
    
  ![soudure moteur](/documentation/Images/soudure_moteur.png)

  Ludovic m'avait donné des Shift Register 74CH595 (Shift Register SIPO), en me reseignant j'ai découvert la distinction entre un Shift Register SIPO et un     Shift Register PISO.
  En expliquant mes nécessités à M. Juan il m'a trouvé des Shift Register PISO (SN74LS165AN)

  ![Shift Register](/documentation/Images/Shift_Register.png)

- ##### Connectique Bluetooth
  Avec Ludovic, nous avons connecté deux esclaves (module Bluetooth HC06) à un maître (module Bluetooth HC05), nous avons réussi à les appareiller ensemble     mais nous n'avons pas pu les tester faute de port USB.

  
  - ##### Gestion du hardware
  La manette étant trop épaisse nous cherchons un agencement prenant moins de place pour essayer de réduire la hauteur de cette dernière.
  Nous sommes arrivés à la conclusion que remplacer l'arduino nano et le module HC06 par un XIAO esp32-s3 nous permetrait de gagner 50 millimètres de      
  hauteur.

  ![agencement V1](/documentation/Images/agencementV1.png)
