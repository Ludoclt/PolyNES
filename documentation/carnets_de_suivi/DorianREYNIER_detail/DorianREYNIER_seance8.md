*******************
# Compte rendu 
*******************
## Séance du 19 Février

- ##### Résolution de problème
  Aprèe test la pcb des manettes de fonctionnait pas, j'ai donc fait de nombreux tests pour chercher l'origine de la panne, nottement replacer le controleur, remplacer le rejistre à décalalage, verifier qu'il n'y ai pas de cour-circuit avec le tester de continuité du multimètre, verifier que tout les composants soient bien alimentés. En cour j'ai pu utiliser un oscilloscope et essayer de trouver l'origine du problème en en comparant les signaux de la clock avec ceux de sorti du registre. J'en suis venu à la conclusion que le problème venait de la résistance trop importante. J'ai donc ajouté un résistance de 820/830 Ω en parallèles avec celle de 10kΩ déjà présente.
  Remerciement: M Masson pour son aide dans la résolution du problème

  ![pcb manette + resistance](/documentation/Images/pcbResistant.png)
  ![Oscillo](/documentation/Images/oscillo.png)


- ##### Soudure
 
  J'ai souder 16 résistances en plus sur la PCB des mannettes.      

  ![pcb manette + resistance](/documentation/Images/pcbResistant.png)

  J'ai également soudé de nobreuses pièces pour d'autres groupes, tel que trois bouttons, une antenne radio, des fils sur un module, deux moteurs...
  
- ##### 3D
  J'ai récupéré les impréssions 3D lancées durant la semaine, je les ai désuporisées, poncé les impurtées, peint les pièces de couleurs différentes, inséré et coller des aimants dans les manettes, ajouté des insert dans le bloc principale, tailler les vis a la bonne taille...
  
- ##### Conception du systeme de batterie

J'utiliserai deux cellules 18650 pour avoir une tention suppérieur à 5V (7.4V) avec un régilateur de tention vers 5V. Je connecte un fil sur les borne d'une piles pour connecter mon arduino en m'en servir de voltmètre pour connaitre la tention de la batterie, donc son niveau de batterie. 


  ![branchement batterie](/documentation/Images/branchementBatterie.png)
