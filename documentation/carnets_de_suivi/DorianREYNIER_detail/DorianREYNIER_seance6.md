*******************
# Compte rendu 
*******************
## Séance du 5 Février

- ##### Réception des composants commandés
  Nous avons reçu le materiel commandé avant les vacances de Noël tel que des ports USB C, des boutons avec embouts de couleurs, un joystick...  
  J'ai également recupéré un troisième esp32 C3  
 
  ![USBC](/documentation/Images/USBC.png)


- ##### Soudure
 
  Comme à chaque fois, l'esp32 était neuf, jai donc soudé les GPIO mâles dessus. Un camarade m'a demandé de lui souder les siens, ce que j'ai fait.       

  ![ESP32-C3_2](/documentation/Images/ESP32-C3_2.png)

  Les tests du Shift register étant concluants, j'ai installé le composant sur ma plaque d'essai et j'y ai soudé les boutons.  
  J'ai dû souder des résistances sur les boutons car l'usage du pullup est impossible combiné avec un Shift register.  
  ![pcb_recto](/documentation/Images/pcb_recto.png)    
  ![pcb_verso](/documentation/Images/pcb_verso.png)
  
- ##### Connectique Bluetooth
  J'ai également réussi à établir la connection Bluetooth entre deux esp32 (un serveur et un client) grâce aux codes exemples fournis dans la bibliothèque BLE.
  Pour la prochaine séance, je vais tester ce même code pour faire communiquer deux clients avec le serveur.

- ##### Test impression
  J'ai lancé une impression 3D d'un bout de la coque principale du projet pour vérifier qu'elle soit assez solide pour supporter le retrait des cartouches.  
  ![test3D](/documentation/Images/test3D.png)
  
