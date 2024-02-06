*******************
# Compte rendu 
*******************
## Séance du 5 Févirer

- ##### Réception des composants commandés
  Nous avons reç le materiel commandé avant les vacances de noël tel que des ports USB C, des boutons avec embouts de couleurs, un joystick...  
  J'ai également recupérer un troisième esp32 C3  
 
  ![USBC](/documentation/Images/USBC.png)


- ##### Soudure
 
  Comme à chaque fois l'esp32 était neuf, jai donc soudé les GPIO mâles dessus. Un camarade m'a demandé de lui soudé les siens, ce que j'ai fait.       

  ![ESP32-C3_2](/documentation/Images/ESP32-C3_2.png)

  Les tests du Shift register étant concluants, j'ai installé le composant sur ma plaque d'essai et j'y ai soudé les bouttons.  
  j'ai du souder des resistances sur les bouton car l'usage du pullup est impossible combiné avec un Shift register.  
  ![pcb_recto](/documentation/Images/pcb_recto.png)    
  ![pcb_verso](/documentation/Images/pcb_verso.png)
  
- ##### Connectique Bluetooth
  J'ai également reussi à établir la connection Bluetooth entre deux esp32 (un serveur et un client) grâce aux codes exemples fourni dans la bibliotheque BLE.
  Pour la prochaine scéance, je fais tester ce même pour faire communiquer deux client avec le serveur.

- ##### Test impression
  J'ai lancé un impression 3D d'un bout de la coque principale du projet pour vérifier quel soit assez solide pour supporter le retré des cartouches.  
  ![test3D](/documentation/Images/test3D.png)
  
