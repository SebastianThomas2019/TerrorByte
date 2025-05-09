#include <Arduino.h>
#include <SoftwareSerial.h>
#include "HUSKYLENS.h"

SoftwareSerial mySerial(0, 1); // RX, TX
HUSKYLENS huskylens;
const int ledPin = 13;
const int summerPin = 12;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(summerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(summerPin, LOW);

  Serial.begin(9600);
  mySerial.begin(9600);

  if (!huskylens.begin(mySerial)) {
    Serial.println("HuskyLens not connected!");
    while (1);
  }

  Serial.println("HuskyLens connected!");
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);
}

void loop() {
  if (huskylens.request()) {
    if (huskylens.available()) {
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
        digitalWrite(ledPin, HIGH);
        digitalWrite(summerPin, LOW);
        Serial.println("ID 1 detected, LED ON");
      } 
      else if (id2Detected)
      {
        digitalWrite(ledPin, LOW);
        digitalWrite(summerPin, HIGH);
        Serial.println("ID 2 detected, SUmmer ON");
      }
      else 
      {
        digitalWrite(ledPin, LOW);
        digitalWrite(summerPin, LOW);
        Serial.println("ID not 1, LED OFF");
      }
    } 
    else 
    {
        digitalWrite(ledPin, LOW); // Turn off the LED if no data is available
        Serial.println("No object detected, LED OFF");
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // Turn off the LED if request fails
    Serial.println("Request failed, LED OFF");
  }
  delay(100);
}
