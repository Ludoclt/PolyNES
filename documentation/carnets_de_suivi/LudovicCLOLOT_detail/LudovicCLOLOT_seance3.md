*******************
# Compte rendu 
*******************

## Séance du 11 Janvier

- ### Début de l'écriture du code qui permet de récupérer les données de la cartouche
  Cette ébauche de code permet de récupérer un octet du programme du jeu à l'adresse spécifiée.

- ### Branchement de l'écran et de l'adaptateur microSD à l'Arduino Due
  En attendant d'avoir un lecteur de cartouches et une sortie vidéo VGA complètement fonctionnelle, on utilisera un écran TFT LCD ainsi qu'une carte microSD dans laquelle seront sauvegardé les jeux pour effectuer des tests.
  ![due-tft-sd](/documentation/Images/due-tft-sd.png)

- ### Test de l'adaptateur microSD
  Test de la carte microSD en affichant les caractéristiques et les fichiers présents dessus.
  ![test-sd](/documentation/Images/test-sd.png)

- ### Test de l'écran TFT
  Test de l'écran TFT en y affichant des formes arbitraires.
  ![test-tft](/documentation/Images/test-tft.png)

- ### Montage de la prise VGA
  ![schema-vga](/documentation/Images/schema-vga.png)  
  Réalisation du montage avec Dorian de la prise VGA en respectant le schéma ci-dessus, ce montage permet seulement d'afficher de la vidéo monochrome, il faudra donc le modifier à l'avenir, de même pour la bibliothèque VGA trouvée sur internet.
  ![branchementVGAV1](/documentation/Images/branchementVGAV1.png)

- ### Test de l'affichage VGA
  Nous avons testé l'affichage VGA avec Dorian à la fin de la séance en affichant simplement le mot "TEST" sur le vidéoprojecteur.

- ### Divers
  Aide à un collègue sur la mise en place d'une communication entre deux modules HC-12.
