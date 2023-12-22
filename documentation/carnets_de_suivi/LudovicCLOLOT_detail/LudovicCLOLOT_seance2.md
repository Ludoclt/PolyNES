*******************
# Compte rendu 
*******************

## Séance du 21 Décembre

- ### Début de l'écriture du code des manettes
  Début de l'écriture du code qui permet d'établir la communication entre la carte principale et les manettes, pour l'instant le maitre HC-05 communique avec seulement un esclave HC-06 et l'état des boutons est affiché dans le moniteur série.  
  exemple avec le code de l'esclave:
  ```cpp
  #include <SoftwareSerial.h>

  #define RX 11
  #define TX 12
  
  #define BUTTON_A 3
  #define BUTTON_B 2
  
  struct ControllerData
  {
    bool A;
    bool B;
  };
  ControllerData data;
  ControllerData lastData;
  
  SoftwareSerial BlueT(RX,TX);
  
  void setup(){
    Serial.begin(9600);
    BlueT.begin(38400);
  
    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
  
    data = (ControllerData) {false, false};
    lastData = data;
  }
  
  void loop(){
    data.A = !digitalRead(BUTTON_A);
    data.B = !digitalRead(BUTTON_B);
    if (memcmp(&data, &lastData, sizeof(ControllerData))) {
      BlueT.write((byte *)&data, sizeof(ControllerData));
      Serial.println("A : " + String(data.A) + " B : " + String(data.B));
      lastData = data;
    }
  }
  ```

- ### Divers
  Aide à un collègue sur l'utilisation d'un écran lcd.  
  Récupération du matériel nécessaire à la lecture des cartouches (plus grosse carte, shift registers...).
