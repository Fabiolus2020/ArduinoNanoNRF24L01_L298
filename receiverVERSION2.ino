//This sketch leverage Pulse with Modulation using the L298N Dual H Bridge Motor Driver (PWM PIN ON ARDUINO ARE 3,5,6,9,10,11
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define enA 6  
#define in1 7
#define in2 5
#define enB 3   
#define in3 4
#define in4 2

RF24 radio(8,9); // CE, CSN
const byte address[6] = "00001";
char receivedData[32] = "";
int xAxis = 512;
int yAxis = 512;
int motorSpeedA = 0;
int motorSpeedB = 0;
int joystick[2]; 

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
  digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void loop() {

  if (radio.available()) {   // If the NRF240L01 module received data
     
      radio.read( joystick, sizeof(joystick) );

    radio.read(&receivedData, sizeof(receivedData));
    yAxis = joystick[0];
    xAxis = joystick[1];
    
    Serial.println(yAxis);
    Serial.println(xAxis);

  }
  
  if (yAxis < 512) {

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    motorSpeedA = map(yAxis, 512, 0, 0, 255);
    motorSpeedB = map(yAxis, 512, 0, 0, 255);
  }
  else if (yAxis > 512) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    
    motorSpeedA = map(yAxis, 512, 1023, 0, 255);
    motorSpeedB = map(yAxis, 512, 1023, 0, 255);
  }

  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  if (xAxis < 512) {
    
    int xMapped = map(xAxis, 512, 0, 0, 255);
    
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
  if (xAxis > 512) {
    
    int xMapped = map(xAxis, 512, 1023, 0, 255);
    
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
  
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
}
