
*/
//communication 1 way
//firstly download library https://github.com/nRF24/RF24

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8, 9); // CE, CSN
const byte address[6] = "00001"; //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.


char xyData[32] = "";
int joystick[2];


void setup()
{
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

void loop()
{

  radio.write( joystick, sizeof(joystick) );

  delay(100);
}
