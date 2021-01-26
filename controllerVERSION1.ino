// Library: TMRh20/RF24, https://github.com/tmrh20/RF24/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 myRadio(8, 9); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";





struct package
{
  int joyposX;
  int joyposY;
};

typedef struct package Package;
Package data;

// Define Joystick Connections
#define joyX A0
#define joyY A1

// Define Joystick Values - Start at 512 (middle position)
int joyposX = 512;
int joyposY = 512;

void setup() {
  Serial.begin(9600);
  myRadio.begin();
  myRadio.setChannel(115);

 //set the address
 myRadio.openWritingPipe(address);
 myRadio.setPALevel(RF24_PA_MAX);
 myRadio.setDataRate( RF24_250KBPS );

//Set module as transmitter
myRadio.stopListening();

  delay(100);
}
void loop() {
  myRadio.write(&data, sizeof(data));
  
  data.joyposX = analogRead(joyX);
  data.joyposY = analogRead(joyY);

//Serial.print("xAxis :");
//Serial.println(data.joyposX);
//Serial.print("yAxis :");
//Serial.println(data.joyposY);
  delay(20);

}
