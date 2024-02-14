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