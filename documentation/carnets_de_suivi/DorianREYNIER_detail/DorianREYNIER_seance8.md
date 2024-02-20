*******************
# Compte rendu 
*******************
## Séance du 19 Février

- ##### Résolution de problème
  Après test la pcb des manettes ne fonctionnait pas, j'ai donc fait de nombreux tests pour chercher l'origine de la panne, notamment replacer le contrôleur, remplacer le registre à décalage, vérifier qu'il n'y ait pas de court-circuit avec le tester de continuité du multimètre, vérifier que tous les composants soient bien alimentés. En cours j'ai pu utiliser un oscilloscope et essayer de trouver l'origine du problème en en comparant les signaux de la clock avec ceux de sortie du registre. J'en suis venu à la conclusion que le problème venait de la résistance trop importante. J'ai donc ajouté une résistance de 820/830Ω en parallèle avec celle de 10kΩ déjà présente.
  Remerciement: M. Masson pour son aide dans la résolution du problème

  ![pcb manette + resistance](/documentation/Images/pcbResistant.png)
  ![Oscillo](/documentation/Images/oscillo.png)


- ##### Soudure
 
  J'ai soudé 16 résistances en plus sur la PCB des mannettes.      

  ![pcb manette + resistance](/documentation/Images/pcbResistant.png)

  J'ai également soudé de nombreuses pièces pour d'autres groupes, tel que trois boutons, une antenne radio, des fils sur un module, deux moteurs...
  
- ##### 3D
  J'ai récupéré les impressions 3D lancées durant la semaine, je les ai désuporisées, poncé les impuretés, peint les pièces de couleurs différentes, inséré et coller des aimants dans les manettes, ajouté des inserts dans le bloc principal, tailler les vis a la bonne taille...
  
- ##### Conception du systeme de batterie

  J'utiliserai deux cellules 18650 pour avoir une tention suppérieure à 5 V (7.4 V) avec un régulateur de tention vers 5 V. Je connecte un fil sur les bornes d'une pile pour connecter mon arduino en m'en servir de voltmètre pour connaitre la tension de la batterie, donc son niveau de batterie. 


  ![branchement batterie](/documentation/Images/branchementBatterie.png)

- ##### création d'autocolants

  N'étant pas satifait de la première tentative de conception d'un autocollant, j'ai recommencé. Cette fois j'ai reproduit l'autocollant de la NES dans un thème polytech.  
  J'ai également commencé à faire un sicker pour les manettes pour imiter les couleurs d'une vraie mais à cause des nombreuses manipulations de la manette, je ne suis pas sur de les installer.
  
![trappe nes](/documentation/Images/trappeNES.png)
![logoPES](/documentation/Images/logoPES.svg)
