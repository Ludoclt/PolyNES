
*******************
# Compte rendu 
*******************

## Description

Console rétro NES (1987) de salon, émulée par Arduino, avec la particularité de pouvoir lire les cartouches originales. La Poly-NES accepte jusqu'à deux joueurs à l'aide de manettes sans fils.

## Séance du 13 Décembre

  - ##### Réalisation de la majorité du [dessin 3D du boitier de la Poly-nes](/boitier) sur le logiciel *onshape*
  Le boîtier de la console, dans lequel nous installerons par la suite tous les composants électroniques, est modélisé grâce à *onshape* dans le but de l'imprimer en 3D.
  
![nes3d](/documentation/Images/nes3d.png)
  
  - ##### Soudure des headers GPIO sur une carte arduino NANO
  Nous avons fait l'acquisition de deux cartes arduino NANO neuves afin de réaliser le circuit des manettes. Les cartes étant neuves, aucun GPIO n'était soudé
 dessus, j'ai donc dû le faire.
 
  Ayant quelques bases en soudage, j'ai aidé certains de mes camarades qui avaient des soudures à réaliser pour leur projet, tel que des moteurs.
  
![pinNanoD](/documentation/Images/pinNanoD.png)

 - ##### Anticipation de la prochaine séance

  Nous avons récupéré une carte arduino DUE, deux cartes arduino nano, deux paires de module Bluetooth (Maîtres et esclaves) pour commencer à étudier le fonctionnement de la communication entre deux arduinos grâce au BlueTooth ainsi que le code qui va avec.
  Indépendamment du Bluetooth, nous avons récupéré deux joysticks dans la même optique de se familiariser avec le composant.
