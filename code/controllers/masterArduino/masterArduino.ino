#include <SoftwareSerial.h>
//Brancher tx sur 2 et rx sur 3
SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  Serial.begin(38400);

  mySerial.begin(38400);
  Serial.println("Arduino Sender");

  mySerial.print("AT\r\n");
  updateSerial();
  delay(200);
}

void updateSerial(void)
{
}

void loop()
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}