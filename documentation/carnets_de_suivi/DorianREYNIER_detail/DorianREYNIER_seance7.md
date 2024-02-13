*******************
# Compte rendu 
*******************
## Séance du 12 Févirer

- ##### Modification du cahier des charges
  Après installation, nous nous sommes rendu compte que l'ajout d'un joystick était inutile. En effet le joystick étant digital et la nes comprennant le        numérique, le joystick est injouable (il faut aller tout au bout de la course pour qu'il soit détecté). Ne représantant pas de défit technique (lecture de    deux potentiomères), nous avons pris la décision de le retirer.
  Ce retrait implique une retuouche sur le modèle 3D pour retirer son logement [dessin 3D de la manette sans joystick](/boitier/manette     V3).
 
  ![Manette V3](/documentation/Images/manette_V3.png)


- ##### Soudure
 
  J'ai touvé un montage plus efficace pour les pcb des manettes, j'ai donc due désouder tout les fils et refaire le montage du début.    

  ![PCB V2](/documentation/Images/pcbV2.png)

    J'ai également commencé a faire une carte video pour transformer la sortie de huit sorties par composantes vers une sortie par            composante pour le vga
  
  ![PCB video](/documentation/Images/pcb_video.png)

  Comme a mon habitude j'ai soudé des cables sur de moteurs ainsi que des bouttons et des headers sur des modules diverses pour les autres groupes.
  
- ##### Connectique Bluetooth
  J'ai également reussi à établir la connection Bluetooth entre deux esp32 (un serveur et un client) grâce aux codes exemples fourni dans la bibliotheque BLE.
  Pour la prochaine scéance, je fais tester ce même pour faire communiquer deux client avec le serveur.

- ##### Test impression
  J'ai lancé un impression 3D d'un bout de la coque principale du projet pour vérifier quel soit assez solide pour supporter le retré des cartouches.  
  ![test3D](/documentation/Images/test3D.png)
  

