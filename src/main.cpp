#include "TerrorByte.h"
#include <Arduino.h>

const int PIN_POWER_BTN = 0;
const int MIN_DISTANCE = 20; //cm

TerrorByte terrorByte;

void onPowerButtonPressed();

// put function declarations here:
int myFunction(int, int);

void setup()
{
  attachInterrupt(digitalPinToInterrupt(PIN_POWER_BTN), onPowerButtonPressed, RISING);
}

void loop()
{

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
void onPowerButtonPressed()
{
  terrorByte.powerButtonPressed();
}