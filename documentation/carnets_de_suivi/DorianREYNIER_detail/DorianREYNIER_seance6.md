*******************
# Compte rendu 
*******************
## Séance du 18 Janvier

- ##### Soudure
  Nous avons récupéré du matériel pour avancer dans le projet:  
    
  j'ai soudé quelques des GPIO mâles sur de nouveaux level shifter fournis par le professeur ainsi que sur deux ESP32-C3 que M. Masson nous fournit en       
  remplacement des XIAO ESP32-S3.
  
  ![Header level shifter](/documentation/Images/headshifter2.png)
  ![ESP32-C3](/documentation/Images/ESP32-C3.png)

  J'ai soudé pas mal de matériel pour d'autres groupes tel que des moteurs, des GPIO, des câbles...
    
  ![soudure moteur](/documentation/Images/soudure_moteur.png)

  Ludovic m'avait donné des Shift register 74CH595 (Shift register SIPO), en me renseignant j'ai découvert la distinction entre un Shift register SIPO et un     Shift register PISO.  
  En expliquant mes nécessités à M. Juan il m'a trouvé des Shift register PISO (SN74LS165AN)

  ![Shift Register](/documentation/Images/Shift_Register.png)

  J'ai d'abord essayé le Shift register avec un bouton sur une arduino nano, le montage réussi, j'ai reproduit le montage sur un ESP32-C3, mais il n'a          fonctionné tout de suite. En cherchant j'ai découvert que la connexion est désactivée de base sur ces ESP32-C3, après réactivation dans l'onglet outil de    l'IDE Arduino, tout a fonctionné comme souhaité.

  ![Montage Shift Register](/documentation/Images/Montage_Shift_Register.png)
  ![Test Shift Register](/documentation/Images/tst_shift_registers.png)
```cpp
// code pour tester registre à décalage
//PL pin1
int load = 7;

//CE pin 15
int clockEnablePin = 4;

//Q7 pin 7
int dataIn = 5;

//CP pin2
int clockIn = 6;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(load, OUTPUT);
pinMode(clockEnablePin, OUTPUT);
pinMode(clockIn, OUTPUT);
pinMode(dataIn, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(load, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  delayMicroseconds(5);

  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnablePin, LOW);
  byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin, HIGH);
  Serial.print("Pin States:\r\n");
  Serial.println(incoming, BIN);
  delay(200);

}
```
  
- ##### Connectique Bluetooth
  Pendant la fin du cours, j'ai commencé les recherches pour mettre en place un connexion bluetooth entre les ESP32-C3, un agissant comme un serveur et     l'autre comme un client.

Une fois le problème du bluetooth résolue il ne restera plus que le montage final des manettes.
