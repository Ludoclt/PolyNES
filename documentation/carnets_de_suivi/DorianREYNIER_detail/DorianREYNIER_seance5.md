*******************
# Compte rendu 
*******************
## Séance du 18 Janvier

- ##### Soudure
  Nous avons recupéré du materiel pour avancer dans le projet:  
    
  J'ai soudé quelques des GPIO mâles sur de nouveaux level shifter fournis par le professeur ainsi que sur deux ESP32-C3 que M. Masson nous fournit en   remplacement des XIAO ESP32-S3.
  
  ![Header level shifter](/documentation/Images/headshifter2.png)
  ![ESP32-C3](/documentation/Images/ESP32-C3.png)

  J'ai soudé pas mal de materiel pour d'autre groupes tel que des moteurs, des GPIO, des câbles...
    
  ![soudure moteur](/documentation/Images/soudure_moteur.png)

  Ludovic m'avait donné des Shift Register 74CH595 (Shift Register SIPO), en me reseignant j'ai découvert la distinction entre un Shift Register SIPO et un     Shift Register PISO.  
  En expliquant mes nécessités à M. Juan il m'a trouvé des Shift Register PISO (SN74LS165AN)

  ![Shift Register](/documentation/Images/Shift_Register.png)

  J'ai d'abord essayé le Shift Register avec un bouton sur une arduino nano, le montage réussi, j'ai reproduit le montage sur un ESP32-C3, mais il n'a          fonctionné tout de suite. En chechant j'ai découvert que le La connection est désactivée de base sur ces ESP32-C3, après réactivatrion dans l'onglet outil    de l'IDE Arduino, tout à fonctionné comme souhaité.

  ![Montage Shift Register](/documentation/Images/Montage_Shift_Register.png)
  ![Test Shift Register](/documentation/Images/tst_shift_registers.png)
  
  
- ##### Connectique Bluetooth
  Pendant la fin du cours, j'ai commancé les recherches pour mettre en place un connection bluetooth entre les ESP32-C3, un agissant comme un serveur et     l'autre comme un client.

Une foie le problème du bluetooth résolue il ne restera plus que le montage final des manettes.
