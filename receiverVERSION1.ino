// Library: TMRh20/RF24, https://github.com/tmrh20/RF24/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 myRadio(8, 9); // CE, CSN

//const byte address[6] = "00001";
byte addresses[][6] = {"0"};

//char receivedData[32] = "";
//int  xAxis, yAxis;


struct package
{
  int xAxis;
  int yAxis;
};

typedef struct package Package;
Package data;

#define enA 10   // Note: Pin 9 in previous video ( pin 10 is used for the SPI communication of the NRF24L01)
#define in1 4
#define in2 5
#define enB 3   // Note:  Pin 10 in previous video
#define in3 6
#define in4 7



int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {
  Serial.begin(9600);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}


void loop() {
  if ( myRadio.available())
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
   // Serial.print("X : ");
   // Serial.println(data.xAxis);
   // Serial.print("Y : ");
  //  Serial.println(data.yAxis);



    // X-axis used for forward and backward control
    if (data.xAxis < 470) {
      // Set Motor A backward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Set Motor B backward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.xAxis, 470, 0, 0, 255);
      motorSpeedB = map(data.xAxis, 470, 0, 0, 255);
    }
    else if (data.xAxis > 550) {
      // Set Motor A forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Set Motor B forward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.xAxis, 550, 1023, 0, 255);
      motorSpeedB = map(data.xAxis, 550, 1023, 0, 255);
    }
    // If joystick stays in middle the motors are not moving
    else {
      motorSpeedA = 0;
      motorSpeedB = 0;
    }


    // Y-axis used for left and right control
    //this is left
    if (data.yAxis < 470) {

      // Set Motor A forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Set Motor B backward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.yAxis, 470, 0, 0, 255);
      motorSpeedB = map(data.yAxis, 470, 0, 0, 255);
    }


    if (data.yAxis > 550) {

      // Set Motor A forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Set Motor B backward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.yAxis, 550, 1023, 0, 255);
      motorSpeedB = map(data.yAxis, 550, 1023, 0, 255);
    }
    // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
    if (motorSpeedA < 70) {
      motorSpeedA = 0;
    }
    if (motorSpeedB < 70) {
      motorSpeedB = 0;
    }
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  }

}
