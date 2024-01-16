#include <SoftwareSerial.h>

#define BT_NAME   "BT_Slave"

#define SLAVE_ADDRESS "98d3,31,8095c3"  //98d3:31:8095c3

#include <SoftwareSerial.h>
//Brancher tx sur 2 et rx sur 3
SoftwareSerial BT(2,3); 

void setup(){
  Serial.begin(38400);

  BT.begin(38400);
  Serial.println("Arduino Sender");
  
  BT.print("AT");

}

void loop(){
  if (BT.available()){
    Serial.write(BT.read());  // les données reçues par le port BT sont envoyées au moniteur série
  }
  if(Serial.available()) {
    BT.write(Serial.read()); // les données reçues par le moniteur série sont envoyées au port BT
  }
}