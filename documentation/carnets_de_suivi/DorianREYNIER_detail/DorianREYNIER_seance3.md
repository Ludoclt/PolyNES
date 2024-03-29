*******************
# Compte rendu 
*******************
## Séance du 11 Janvier

- ##### Soudure des headers GPIO sur une carte STM32
  La carte STM32 que nous avons pour le projet n'avait aucun header soudé dessus, j'ai donc soudé des headers femelles pour simplifier les prochains branchements tels que ceux du lecteur de cartouche.
  
  ![STM32_headers](/documentation/Images/STM32headers.png)
  
  Nous avons reçu les prises VGA commandées sur AliExpress. J'ai soudé les câbles dessus en respectant le schéma de montage sélectionné par Ludovic.
  
  ![VGA_V1](/documentation/Images/VGAV1.png)

  - ##### Test d'affichage
  Avec Ludovic, nous avons réalisé le montage de la prise VGA sur un arduino uno. Nous avons réussi à afficher le texte "TEST" sur le vidéo-projecteur de la salle.
  
  ![branchement_VGA_V1](/documentation/Images/branchementVGAV1.png)

  - ##### Conception de plaques de test
  Pour éviter la fabrication de PCB, j'ai réalisé deux plaques de tests contenant l'ensemble des boutons nécessaires à la manette: quatre en forme de croix pour la "croix directionnelle", deux centrés pour les boutons "Select" et "Start" et deux boutons jaunes pour les touches d'actions "A" et "B".\
  J'ai également retaillé les plaques pour qu'elle soit les plus petites possibles et prennent le moins de place dans le boîtier de la manette.
   
  ![Pcb_manette](/documentation/Images/pcbmanette.png)
  
- ##### Finalisation du [dessin 3D de la manette V2](/boitier/manettev2.stl) sur le logiciel *onshape*
  Amélioration des finitions et des détails de la manette, ajout de quatres trous pour insérer des leds pour créer un indicateur de batterie, ajout d'un emplacement pour un interrupteur d'allumage de la manette, création d'un emplacement pour une prise USB-C.
  
  ![manette_V2_3D](/documentation/Images/manettev23D.png)
    
  - ##### Test de taille du modèle 3D
  J'ai réalisé une première impression 3D de mauvaise qualité pour vérifier que la taille, la forme ainsi que l'emplacement des boutons et autres composants me conviennent.

  ![manette_V1](/documentation/Images/manetteV1.png)
  ![manette_V1_profil](/documentation/Images/manetteV1profil.png)
  
  Les modifications pour la V2 de la manette sont axées sur les deux boutons que j'avais oubliés au milieu de la manette (les boutons Start and Select). \
  Dans mon idée de faire un mélange entre une manette de N64 et une manette de NES, le placement des boutons A et B (les jaunes) n'était pas adapté donc je les ai mis en diagonale au lieu d'en ligne.\
  J'ai réimprimé la couche supérieure du modèle pour être sûr de ne pas faire d'erreur:

  ![manette_V2](/documentation/Images/manetteV2.png)

  Pour référence, voici une photo d'une manette de Nintendo 64, manette considérée comme une des pires manettes développées.
  ![manette_N64](/documentation/Images/manetteN64.png)
