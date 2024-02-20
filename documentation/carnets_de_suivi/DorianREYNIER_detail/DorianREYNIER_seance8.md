*******************
# Compte rendu 
*******************
## Séance du 19 Février

- ##### Résolution de problème
  Après test, la PCB des manettes ne fonctionnait pas, j'ai donc fait de nombreux tests pour chercher l'origine de la panne, notamment remplacer le contrôleur, remplacer le registre à décalage, vérifier qu'il n'y ait pas de court-circuit avec le testeur de continuité du multimètre, vérifier que tous les composants soient bien alimentés. En cours j'ai pu utiliser un oscilloscope et essayer de trouver l'origine du problème en comparant les signaux de la clock avec ceux de sortie du registre. J'en suis venu à la conclusion que le problème venait de la résistance trop importante. J'ai donc ajouté une résistance de 820/830Ω en parallèle avec celle de 10kΩ déjà présente.
  Remerciement: M. Masson pour son aide dans la résolution du problème

  ![pcb manette + resistance](/documentation/Images/pcbResistant.png)
  ![Oscillo](/documentation/Images/oscillo.png)


- ##### Soudure
 
  J'ai soudé 16 résistances en plus sur la PCB des manettes.      

  ![pcb manette + resistance](/documentation/Images/pcbResistant.png)

  J'ai également soudé de nombreuses pièces pour d'autres groupes, tel que trois boutons, une antenne radio, des fils sur un module, deux moteurs...
  
- ##### 3D
  J'ai récupéré les impressions 3D lancées durant la semaine, je les ai désuporisées, poncé les impuretés, peint les pièces de couleurs différentes, inséré et collé des aimants dans les manettes, ajouté des inserts dans le bloc principal, taillé les vis à la bonne taille...

  ![Boiter 3D](/documentation/Images/Boitier3D.png)
  ![3D manette](/documentation/Images/3Dmanette.png)
  ![3D manette démonté](/documentation/Images/3DManetteDemonte.png)
  
- ##### Conception du systeme de batterie

  J'utiliserai deux cellules 18650 pour avoir une tention supérieure à 5 V (7.4 V) avec un régulateur de tention vers 5 V. Je connecte un fil sur les bornes d'une pile pour connecter mon arduino et m'en servir de voltmètre pour connaître la tension de la batterie, donc son niveau de charge. 


  ![branchement batterie](/documentation/Images/branchementBatterie.png)

  Légende:
  fil arduino bleu : lecture du la tension des batteries
  fils arduino noirs : ground du circuit
  fil arduino vert : 5V du circuit
  PCB marron : diviseur de tension pour être supporté par les ports de l'arduino

- ##### Création d'autocollants

  N'étant pas satifait de la première tentative de conception d'un autocollant, j'ai recommencé. Cette fois j'ai reproduit l'autocollant de la NES dans un thème Polytech.  
  J'ai également commencé à faire un sticker pour les manettes pour imiter les couleurs de l'originale mais à cause des nombreuses manipulations de la manette, je ne suis pas sûr de les installer.
  
![trappe nes](/documentation/Images/trappeNES.png)
![logoPES](/documentation/Images/logoPES.svg)

Note: Github fait apparaitre des bugs graphiques mais sur Inkscape le svg est bien affiché.
