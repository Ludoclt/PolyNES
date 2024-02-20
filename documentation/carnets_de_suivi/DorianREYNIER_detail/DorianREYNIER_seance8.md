*******************
# Compte rendu 
*******************
## Séance du 19 Février

- ##### Résolution de problème
  Aprèe test la pcb des manettes de fonctionnait pas, j'ai donc fait de nombreux tests pour chercher l'origine de la panne, nottement replacer le controleur, remplacer le rejistre à décalalage, verifier qu'il n'y ai pas de cour-circuit avec le tester de continuité du multimètre, verifier que tout les composants soient bien alimentés. En cour j'ai pu utiliser un oscilloscope et essayer de trouver l'origine du problème en en comparant les signaux de la clock avec ceux de sorti du registre. J'en suis venu à la conclusion que le problème venait de la résistance trop importante. J'ai donc ajouté un résistance de 820/830 Ω en parallèles avec celle de 10kΩ déjà présente.

  ![pcb manette + resistance](/documentation/Images/pcbResistant.png)
  ![Oscillo](/documentation/Images/oscillo.png)


- ##### Soudure
 
  J'ai souder 16 résistances en plus sur la PCB des mannettes.      

  ![pcb manette + resistance](/documentation/Images/pcbResistant.png)

  J'ai également soudé de nobreuses pièces pour d'autres groupes, tel que trois bouttons, une antenne radio, des fils sur un module, deux moteurs...
  
- ##### Connectique Bluetooth
  J'ai également réussi à établir la connection Bluetooth entre deux esp32 (un serveur et un client) grâce aux codes exemples fournis dans la bibliothèque BLE.
  Pour la prochaine séance, je vais tester ce même code pour faire communiquer deux clients avec le serveur.

- ##### Test impression
  J'ai lancé une impression 3D d'un bout de la coque principale du projet pour vérifier qu'elle soit assez solide pour supporter le retrait des cartouches.  
  ![test3D](/documentation/Images/test3D.png)
  