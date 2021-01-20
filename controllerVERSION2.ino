/*   
 *    Arduino Car NRF24L01
 *    
 *    ForbiddenBit.com
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8,9); // CE, CSN
const byte address[6] = "00001";
char xyData[32] = "";
int joystick[2];
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}
void loop() {

  joystick[0] = analogRead(A1);
  joystick[1] = analogRead(A0);

  Serial.println(joystick[1]);

  
  radio.write( joystick, sizeof(joystick) );
}
