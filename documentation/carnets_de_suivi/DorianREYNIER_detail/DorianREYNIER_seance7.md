*******************
# Compte rendu 
*******************
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
  A cause des nombreux détails ainsi que la struckture, il le remodelage du modèle était aussi long de sa conception.
  
  ![boitier 3D mini](/documentation/Images/boitier_3D_mini.png)
  

