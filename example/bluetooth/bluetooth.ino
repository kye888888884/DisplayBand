#include <SoftwareSerial.h>
 
int RX=15;
int TX=14;
SoftwareSerial bluetooth(RX, TX);

unsigned long past = 0;
unsigned long past_read = 0;
 
void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop(){
  unsigned long now = millis();
//  if (now - past > 1000)
//  {
//    past = now;
//    bluetooth.print("hello");
//    bluetooth.println();
//    Serial.println("hello1");
//  }

  read();
}

void read()
{
  int rxData;
  if (bluetooth.available())
  {
    Serial.println("received!");

//    byte header1 = bluetooth.read();
//    byte header2 = bluetooth.read();
//    byte command = bluetooth.read();
    byte data = bluetooth.read();
//    if (header1 != 0xA5) {
//      Serial.println("1");
//      return;
//    }
//    if (header2 != 0x5A) {
//      Serial.println("2");
//      return;
//    }
//    if (command != 0x01) {
//      Serial.println("3");
//      return;
//    }

    Serial.print("data: ");
    Serial.println(data);
    if (data > 128) {
      Serial.println("good");
      bluetooth.println("good");
    }
    else {
      Serial.println("bad");
      bluetooth.println("bad");
    }
  }
}
