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
  // mySerial.begin(9600);

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