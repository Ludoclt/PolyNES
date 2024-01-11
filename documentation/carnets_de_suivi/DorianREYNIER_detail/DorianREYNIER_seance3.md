*******************
# Compte rendu 
*******************
## Séance du 11 Janvier

- ##### Soudure des headers GPIO sur une carte STM32
  La carte STM32 que nous avons pour le projet n'avait aucun header de soudé dessu, j'ai donc souder des header femelles pour simplifier les prochain branchements tels que ceux du lecteur de cartouche.
  
  ![STM32_headers](/documentation/Images/STM32headers.png)
  
  Nous avons reçut les prises VGA commandés sur aliexpress. J'ai soudé les cables dessus en respectant les schéma de de montage selectionné par Ludovic.
  
  ![VGA_V1](/documentation/Images/VGAV1.png)

  - ##### Test d'affichage
  Avec ludovic, nous avons réalisé le montage de la prise VGA sur un arduino uno. Nous avons réussi à afficher du texte "TEST" sur le vidéo-projecteur de la salle.
  
  ![branchement_VGA_V1](/documentation/Images/branchementVGAV1.png)

  - ##### Conception de Plaque de test
  Pour éviter la fabrication de pcbs, j'ai réalisé deux plaque de tests contenant l'essemble des boutons necessaire à la manette: quatre en forme de croix pour la "croix directionnel", deux centrés pour les bouttons select et start et deux boutons jaunes pour les touche "A" et "B" ,les touches d'actions.
  J'ai également retaillé les plaques pour être le plus pétits possibles et prendre le moins de place dans le boitier de la manette.
   
  ![Pcb_manette](/documentation/Images/pcbmanette.png)
  
- ##### Finalisation du [dessin 3D de la manette V2](/boitier/manettev2) sur le logiciel *onshape*
  Amélioration des finitions et des détails de la manette, ajout deux 4 trous pour insérer des leds pour créer un indicateur de batterie, ajout d'un emplacement pour un interrupteur d'allumage de la manette, création d'un emplacement pour une prise USB-C.
  
  ![manette_V2_3D](/documentation/Images/manettev23D.png)
    
  - ##### Test de taille du mdèle 3D
  J'ai réalisé une première impression 3D de mauvaise qualitée pour vérifier que la taille, la forme ainsi que l'emplacement des boutons et autre composants me conviennent.

  ![manette_V1](/documentation/Images/manetteV1.png)
  ![manette_V1_profil](/documentation/Images/manetteV1profil.png)
  
  Les modifications pour la V2 de la manette sont axés sur les deux bouttons que j'avais oublié au milieu de la manette (les bouttons start and select). \
  Dans mon idée de faire un mélange entre une manette de N64 et une manette de NES, le placement des bouttons A et B (les jaunes) n'était pas adapté donc je les au mis en digonale au lieu d'en ligne.\
  J'ai réimprimé la couche supérieure du modèle pour être sûre de ne pas faire d'erreur:

  ![manette_V2](/documentation/Images/manetteV2.png)

  Pour référence voici une photo d'une manette de Nintendo 64, manette considéré comme une des pires manettes, développés.
  ![manette_N64](/documentation/Images/manetteN64.png)
