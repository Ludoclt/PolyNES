#include <SoftwareSerial.h>

#define RX 10
#define TX 11

struct ControllerData
{
  bool A;
  bool B;
};
ControllerData data;

SoftwareSerial BlueT(RX, TX);

void setup() {
  Serial.begin(9600);
  BlueT.begin(38400);
  data = (ControllerData) {false, false};
}

void loop() {
  if (BlueT.available())
  {
    BlueT.readBytes((byte *)&data, sizeof(ControllerData));
    Serial.println("A : " + String(data.A) + " B : " + String(data.B));
  }
}
