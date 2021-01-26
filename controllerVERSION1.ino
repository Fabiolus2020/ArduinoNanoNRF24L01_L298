
// Library: TMRh20/RF24, https://github.com/tmrh20/RF24/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 myRadio(8, 9); // CE, CSN
byte addresses[][6] = {"0"};

struct package
{
  int xAxis;
  int yAxis;
};

typedef struct package Package;
Package data;


void setup() {
  Serial.begin(9600);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.openWritingPipe( addresses[0]);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
}
void loop() {
  myRadio.write(&data, sizeof(data));
  data.xAxis = analogRead(A0); // Read Joysticks X-axis
  data.yAxis = analogRead(A1); // Read Joysticks Y-axis

//Serial.print("xAxis :");
//Serial.println(data.xAxis);
//Serial.print("yAxis :");
//Serial.println(data.yAxis);
  delay(20);

}
