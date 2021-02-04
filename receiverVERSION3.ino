//Fabiolus
//the_fabiolous@hotmail.com
//Oct_10_2020
//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 myRadio(8, 9); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//byte addresses[][6] = {"0"};

struct package
{
  int motordirection;
};

typedef struct package Package;
Package data;
// Define Joystick Connections
#define joyX A0
#define joyY A1

// Define Joystick Values - Start at 512 (middle position)
int joyposX = 512;
int joyposY = 512;
int motordirection = 0;

void setup()
{

  Serial.begin(9600);
  delay(100);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS );

  //myRadio.openWritingPipe( addresses[0]);
  //set the address
  myRadio.openWritingPipe(address);

  //Set module as transmitter
  myRadio.stopListening();
  delay(100);
}

void loop()
{

  myRadio.write(&data, sizeof(data));
  // Print to Serial Monitor
  // Serial.println("Reading motorcontrol values ");

  // Read the Joystick X and Y positions
  joyposX = analogRead(joyX);
  joyposY = analogRead(joyY);

  // Determine if this is a forward or backward motion
  // Do this by reading the Verticle Value
  // Apply results to MotorSpeed and to Direction

  if (joyposX < 460)
  {
    // This is Forward
    // Set Motors forward
    data.motordirection = 1;
  }
  else if (joyposX > 600)
  {
    // This is backward
    // Set Motors backward
    data.motordirection = 2;
  }

  else if (joyposY > 600)
  {

    // This is left
    // Set Motors backward and forward
    data.motordirection = 3;
  }
  else if (joyposY < 460)
  {
    data.motordirection = 4;
  }

  else {
    data.motordirection = 0;
  }

  //Display the Motor Control values in the serial monitor.
  // Serial.print("motorspeed1: ");
  // Serial.println(data.motorspeed1);
  //  Serial.print(" motorspeed2: ");
  // Serial.println(data.motorspeed2);
  //Serial.print(" - Direction: ");
  //Serial.println(data.motordirection);
  // Serial.print(" Xjoystick: ");
  // Serial.println(joyposX);
  // Serial.print(" Yjoystick: ");
  //Serial.println(joyposY);

  delay(100);  // Wait a bit before next transmission
}
