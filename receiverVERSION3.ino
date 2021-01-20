//communication 1 way
//firstly download library https://github.com/nRF24/RF24

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8, 9); // CE, CSN
const byte address[6] = "00001";

char receivedData[32] = "";
int xAxis = 512;
int yAxis = 512;
int joystick[2];

byte addresses[][6] = {"0"};
int EN1 = 5;
int EN2 = 6;
int EN3 = 3;
int EN4 = 10;




void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  analogWrite(EN3, 0);
  analogWrite(EN4, 0);
}


void loop()
{
  if ( radio.available())
  {
    while (radio.available())
    {
      radio.read( joystick, sizeof(joystick) );

    }

    int yAxis = joystick[0];
    int xAxis = joystick[1];
    
    int forward = map(xAxis, 524, 1024, 0, 255);
    int backward = map(xAxis, 500, 0, 0, 255);
    int right = map(yAxis, 524, 1024, 0, 255);
    int left = map(yAxis, 500, 0, 0, 255);
    
    if (xAxis > 524 && yAxis < 524 && yAxis > 500) {
      analogWrite(EN3, forward);
      analogWrite(EN4, 0);
      analogWrite(EN1, forward);
      analogWrite(EN2, 0);
    } else if (xAxis < 500 && yAxis < 524 && yAxis > 500) {
      analogWrite(EN4, backward);
      analogWrite(EN3, 0);
      analogWrite(EN2, backward);
      analogWrite(EN1, 0);
    } else if (xAxis < 524 && xAxis > 500 && yAxis < 524 && yAxis > 500) {
      analogWrite(EN4, 0);
      analogWrite(EN3, 0);
      analogWrite(EN2, 0);
      analogWrite(EN1, 0);
    } else if (xAxis < 524 && xAxis > 500 && yAxis > 524) {
      analogWrite(EN4, 0);
      analogWrite(EN3, left);
      analogWrite(EN2, left);
      analogWrite(EN1, 0);
    } else if (xAxis < 524 && xAxis > 500 && yAxis < 500) {
      analogWrite(EN4, right);
      analogWrite(EN3, 0);
      analogWrite(EN2, 0);
      analogWrite(EN1, right);
    } else if (xAxis > 524 && yAxis > 524) {
      analogWrite(EN3, forward);
      analogWrite(EN4, 0);
      analogWrite(EN1, forward - right);
      analogWrite(EN2, 0);
    } else if (xAxis > 524 && yAxis < 500) {
      analogWrite(EN3, forward - left);
      analogWrite(EN4, 0);
      analogWrite(EN1, forward);
      analogWrite(EN2, 0);
    } else if (xAxis < 500 && yAxis > 524) {
      analogWrite(EN4, backward);
      analogWrite(EN3, 0);
      analogWrite(EN2, backward - right);
      analogWrite(EN1, 0);
    } else if (xAxis < 500 && yAxis < 500) {
      analogWrite(EN4, backward - left);
      analogWrite(EN3, 0);
      analogWrite(EN2, backward);
      analogWrite(EN1, 0);
    }

  }

}
