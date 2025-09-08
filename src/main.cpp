#define SLAVE

#ifdef MASTER

#include "TerrorByte.h"
#include "pins.h"
#include "motor.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <HUSKYLENS.h>




const int MIN_DISTANCE = 20; //cm

TerrorByte terrorByte;
HUSKYLENS huskylens;
Motor motor(pin::pwmPin, pin::directionPin, pin::brakePin);

SoftwareSerial mySerial(0, 1); // RX, TX

void onPowerButtonPressed();
void huskyLens();

void setup()
{
  pinMode(pin::STATUS_LED, OUTPUT);
  pinMode(pin::BUZZER, OUTPUT);
  digitalWrite(pin::STATUS_LED, LOW);
  digitalWrite(pin::BUZZER, LOW);

  Serial.begin(9600);
  mySerial.begin(9600);

  if (!huskylens.begin(mySerial)) {
    Serial.println("HuskyLens not connected!");
    while (1);
  }

  Serial.println("HuskyLens connected!");
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);

  // Serial.begin(9600);
  // mySerial.begin(9600);pinMode(pin::STATUS_LED, OUTPUT);

  // if (!huskylens.begin(mySerial)) {
  //   Serial.println("HuskyLens not connected!");
  //   while (1);
  // }

  // Serial.println("HuskyLens connected!");
  // huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);

   //attachInterrupt(digitalPinToInterrupt(PIN_POWER_BTN), onPowerButtonPressed, RISING);


  
 }

void loop()
{
  //Serial.println("Still alive");
  huskyLens();

  while (terrorByte.isActive())
  {
    int distances[4] = {0,0,0,0};
    terrorByte.getDistances(&distances[4]);

    while (distances[TerrorByte::FRONT] >= 20)
    {
      terrorByte.driveInDirection(TerrorByte::FRONT);
    }
    while (distances[TerrorByte::LEFT] >= 20 && distances[TerrorByte::FRONT] >= 10)
    {
      terrorByte.driveInDirection(TerrorByte::FRONT_LEFT);
    }
    while (distances[TerrorByte::LEFT] >= 20)
    {
      terrorByte.driveInDirection(TerrorByte::LEFT);
    }
    while (distances[TerrorByte::BACK] >= 20)
    {
      terrorByte.driveInDirection(TerrorByte::BACK);
    }
    while (distances[TerrorByte::RIGHT] >= 20)
    {
      terrorByte.driveInDirection(TerrorByte::RIGHT);
    }
  }
}

// Hardware Interrupt if power Button is pressed. 
// void onPowerButtonPressed()
// {
//   terrorByte.powerButtonPressed();
// }

void huskyLens() 
{
  if (huskylens.request()) 
  {
    if (huskylens.available()) 
    {
      bool id1Detected = false;
      bool id2Detected = false;
      while (huskylens.available()) 
      {
        HUSKYLENSResult result = huskylens.read();
          if (result.ID == 1) 
          {
            id1Detected = true;
            break; // No need to check further if ID 1 is found
          }
          else if (result.ID == 2)
          {
            id2Detected = true;
            break;
          }
        }

      if (id1Detected) 
      {
        Serial.println("TARGET DETECTED");
        motor.turnLeft();
      } 
      else if (id2Detected)
      {
        Serial.println("EXTERMINATE");
        motor.stop();
      }
      else 
      {
        Serial.println("Weiß ich ja nicht, digga");
      }
    } 
    else 
    {
        Serial.println("No object detected");
        motor.stop();
    }
  } 
  else 
  {
    Serial.println("Request failed");
  }
  delay(100);
}

#endif

#ifdef SLAVE

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "pins.h"
#include "motor.h"

Motor MotorLeft(pin::MOTOR_BACK_LEFT_PWM, pin::MOTOR_BACK_LEFT_DIRECTION, pin::MOTOR_BACK_LEFT_BRAKE);
Motor MotorRight(pin::MOTOR_BACK_RIGHT_PWM, pin::MOTOR_BACK_RIGHT_DIRECTION, pin::MOTOR_BACK_RIGHT_BRAKE);

enum master_input
{
  ALL_OFF,            // 000 (0)
  LEFT_FORWARD,       // 001 (1)
  LEFT_BACKWARD,      // 010 (2)
  RIGHT_FORWARD,      // 011 (3)
  RIGTH_BACKWARD,     // 100 (4)
  BOTH_FORWARD,       // 101 (5)
  BOTH_BACKWARD       // 110 (6)

};

void setup()
{
  Serial.begin(9600);
  pinMode(pin::MASTER_CONTROLL_A, INPUT);
  pinMode(pin::MASTER_CONTROLL_B, INPUT);
  pinMode(pin::MASTER_CONTROLL_C, INPUT);
  Serial.println("Slave: Setup done.");
}

void loop()
{
  int master_command = 0;
  int master_input_A = digitalRead(pin::MASTER_CONTROLL_A) < 1 ? 0 : 1;

  int master_input_B = digitalRead(pin::MASTER_CONTROLL_B) < 1 ? 0 : 2;

  int master_input_C = digitalRead(pin::MASTER_CONTROLL_C) < 1 ? 0 : 4;

  master_command = master_input_A + master_input_B + master_input_C;


  switch (master_command)
  {
  case ALL_OFF:
    MotorLeft.stop();
    MotorRight.stop();
    Serial.println("All off");
    break;
  
  case LEFT_FORWARD:
    MotorLeft.turnRight();
    MotorRight.stop();
    Serial.println("Left Motor: Forward.");
    break;

  case LEFT_BACKWARD:
    MotorLeft.turnLeft();
    MotorRight.stop();
    Serial.println("Left Motor: Backward.");
    break;
  
  case RIGHT_FORWARD:
    MotorLeft.stop();
    MotorRight.turnRight();
    Serial.println("Right Motor: Forward.");
    break;

  case RIGTH_BACKWARD:
    MotorLeft.stop();
    MotorRight.turnLeft();
    Serial.println("Right Motor: Backword.");
    break;
  
  case BOTH_FORWARD:
    MotorLeft.turnRight();
    MotorRight.turnRight();
    Serial.println("Both Motors: Forward.");
    break;
  
  case BOTH_BACKWARD:
    MotorLeft.turnLeft();
    MotorRight.turnLeft();
    Serial.println("Both Motors: Backword.");
    break;
  
  default:
    break;
  }

  delay(50);
}

#endif