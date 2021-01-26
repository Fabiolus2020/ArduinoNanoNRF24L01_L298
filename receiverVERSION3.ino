//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 myRadio(8, 9); // CE, CSN
struct package
{
  int motorspeed1;
  int motorspeed2;
  int motordirection;
};

//address through which two modules communicate.
const byte address[6] = "00001";

//byte addresses[][6] = {"0"};

// Motor A Connections
int enA = 10;
int in1 = 4;
int in2 = 5;

// Motor B Connections
int enB = 3;
int in3 = 6;
int in4 = 7;

typedef struct package Package;
Package data;

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  //myRadio.openReadingPipe(1, addresses[0]);

  //set the address
  myRadio.openReadingPipe(0, address);
  myRadio.startListening();
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

  void loop()
  {
    if ( myRadio.available())
    {
      //while (myRadio.available())
      //{
        myRadio.read( &data, sizeof(data) );
      //}

      //Serial Print the values
     // Serial.print(": motorspeed1 :");
    //  Serial.println(data.motorspeed1);
    //  Serial.print(" motorspeed2 :");
    //  Serial.println(data.motorspeed2);
    //  Serial.print(" direction");
     // Serial.println(data.motordirection);
      //delay (2000);
      // Set Motor Direction
      if (data.motordirection == 1)
      {
        // Motors are backwards
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      }

      if (data.motordirection == 0)
      {
        // Motors are forwards
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }

      if (data.motordirection == 3)
      {
        // Motors are forwards
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      }

      if (data.motordirection == 4)
      {
        // Motors are forwards
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }
      // Drive Motors
      analogWrite(enA, data.motorspeed1);
      analogWrite(enB, data.motorspeed2);

    }
    delay(30);
  }
