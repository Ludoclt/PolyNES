*******************
# Compte rendu 
*******************

## Séance du 22 Janvier

- ### Implementation du Pixel Processing Unit
  Le code de l'émulateur est maintenant quasiment terminé, l'implémentation du PPU permet le rendu du fond d'écran et des sprites du jeu. La NES étant conçue pour fonctionner avec des télévisions cathodiques, le rendu d'une frame fonctionne en cycles et scanlines, où un cycle correspond à l'activation et la desactivation du faisceau à éléctrons, donc à l'affichage d'un pixel, et une scanline correspond au balayage complet de l'écran de gauche à droite, ce qui abouti à l'affichage d'une ligne de pixels, cela nous permet donc de nous réperer sur l'écran, où un cycle peut être associé à la coordonnée x et la scanline à la coordonnée y.  
  Ainsi, un cycle (rendu d'un pixel) de l'écran nécessite un cycle du PPU, des opérations sont donc effectuées en permanence pendant le rendu d'une frame, ces opérations respectent le diagramme ci-dessous.  
  ![diagramme](/documentation/Images/diagramme_ppu.png)  
  Pour plus d'informations, consulter la [documentation](https://www.nesdev.org/wiki/PPU_rendering).

  Voici une démonstration de l'émulateur avec le jeu donkey kong :  
  ![demo](/documentation/Images/nes_demo.gif)

- ### Récuperation du jeu sur la carte sd
  En plus de pouvoir jouer à l'aide de la cartouche, la console pourra aussi charger des jeux depuis une carte sd qui contient des fichiers ```.nes```.
  Le header de ce type de fichiers se présente comme suit:  
  ```cpp
  struct Header
  {
      uint8_t constant[4];
      uint8_t prg_rom_size;
      uint8_t chr_rom_size;
      uint8_t mapper_flags_1;
      uint8_t mapper_flags_2;
      uint8_t prg_ram_size;
      uint8_t tv_system_flags_1;
      uint8_t tv_system_flags_2;
      uint8_t unused[5];
  };
  ```
  Le fichier contient une backup des rom PRG et CHR, ainsi que des infos sur le [mapper](https://www.nesdev.org/wiki/Mapper) utilisé (il s'agit en quelque sort du système d'aiguillage de la cartouche).  
  Il nous suffit donc de lire le fichier et stocker les données de manière appropriée dans des variables à l'aide de la librairie standard SD de l'arduino IDE.  
  Encore une fois, pour plus d'informations, consulter la [documentation](https://www.nesdev.org/wiki/INES).
  
