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
  int motorspeed1;
  int motorspeed2;
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
int motorspeed1;
int motorspeed2;

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

  // Set initial motor direction as forward
  int motordirection = 0;
  int motorspeed1 = 0;
  int motorspeed2 = 0;

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
    data.motordirection = 0;

    //Determine Motor Speeds
    // my joystick is positioned upside down so we need to reverse readings
    data.motorspeed1 = map(joyposX, 460, 0, 0, 255);
    data.motorspeed2 = map(joyposX, 460, 0, 0, 255);

  }
  else if (joyposX > 600)
  {
    // This is backward
    // Set Motors backward
    data.motordirection = 1;

    //Determine Motor Speeds
    data.motorspeed1 = map(joyposX, 600, 1023, 0, 255);
    data.motorspeed2 = map(joyposX, 600, 1023, 0, 255);

  }
  else
  {
    // This is Stopped
    data.motordirection = 0;
    data.motorspeed1 = 0;
    data.motorspeed2 = 0;

  }

  // Now do the steering
  // The Horizontal position will "weigh" the motor speed
  // Values for each motor

  if (joyposY > 600)
  {

    // This is left
    // Set Motors backward and forward
    data.motordirection = 3;
    // Move Left
    // As we are going left we need to reverse readings
    // Map the number to a value of 255 maximum
    data.motorspeed1 = map(joyposY, 600, 1023, 0, 255);
    data.motorspeed2 = map(joyposY, 600, 1023, 0, 255);
    //  motorcontrol[0] = motorcontrol[0] - joyposHorz;
    // motorcontrol[1] = motorcontrol[1] + joyposHorz;

    // Don't exceed range of 0-255 for motor speeds
    //  if (motorcontrol[0] < 0)motorcontrol[0] = 0;
    //   if (motorcontrol[1] > 255)motorcontrol[1] = 255;

  }
  else if (joyposY < 460)
  {
    data.motordirection = 4;
    // Move Right
    // Set Motors forward and backward
    // Map the number to a value of 255 maximum
    data.motorspeed1 = map(joyposY, 460, 0, 0, 255);
    data.motorspeed2 = map(joyposY, 460, 0, 0, 255);


    //motorcontrol[0] = motorcontrol[0] + joyposHorz;
    //motorcontrol[1] = motorcontrol[1] - joyposHorz;

    // Don't exceed range of 0-255 for motor speeds
    //  if (motorcontrol[0] > 255)motorcontrol[0] = 255;
    //  if (motorcontrol[1] < 0)motorcontrol[1] = 0;

  }

  // Adjust to prevent "buzzing" at very low speed
  if (data.motorspeed1 < 70)data.motorspeed1 = 0;
  if (data.motorspeed2 < 70)data.motorspeed2 = 0;

  //Display the Motor Control values in the serial monitor.
 // Serial.print("motorspeed1: ");
  // Serial.println(data.motorspeed1);
 //  Serial.print(" motorspeed2: ");
 // Serial.println(data.motorspeed2);
 //  Serial.print(" - Direction: ");
 //  Serial.println(data.motordirection);
  // Serial.print(" Xjoystick: ");
  // Serial.println(joyposX);
  // Serial.print(" Yjoystick: ");
  //Serial.println(joyposY);



  delay(100);  // Wait a bit before next transmission
}
