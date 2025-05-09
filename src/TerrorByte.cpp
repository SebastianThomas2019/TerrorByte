#include "TerrorByte.h"
#include "protothreads.h"
#include <iostream>
#include <string.h>


TerrorByte::TerrorByte()
    : m_poweredON(false)
    , ptr_statusRgb(new RgbLed(1,2,3))
    , m_spaceLeftSide(0)
    , m_spaceRightSide(0)
    , m_spaceFrontSide(0)
    , m_spaceBackSide(0)
{
    pinMode(PIN_LEDS_FRONT, OUTPUT);
    pinMode(PIN_LEDS_BACK, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
};

void TerrorByte::powerButtonPressed()
{
    if (m_poweredON)
    {
        m_poweredON = false;
        ptr_statusRgb->setColor(RgbLed::WHITE);

        digitalWrite(PIN_LEDS_FRONT, LOW);
        digitalWrite(PIN_LEDS_BACK, LOW);
    }
    else
    {
        m_poweredON = true;
        ptr_statusRgb->setColor(RgbLed::GREEN);

        digitalWrite(PIN_LEDS_FRONT, HIGH);
        digitalWrite(PIN_LEDS_BACK, HIGH);
    }
};

void TerrorByte::getDistances(int array[4])
{
    measureDistance();

    if (sizeof(array) >= 4 * sizeof(int))
    int distances[4]
    {
        [LEFT]  = m_spaceLeftSide,
        [RIGHT] = m_spaceRightSide,
        [FRONT] = m_spaceFrontSide,
        [BACK]  = m_spaceBackSide
    };

    return;
};

bool   TerrorByte::driveInDirection(direction_t direction)
{
    //This methode still needs to be implemented.
    std::string directionStr = "";

    switch (direction)
    {
    case LEFT:
        directionStr = "Left";
        break;
    
    case RIGHT:
        directionStr = "Right";
        break;
    
    case FRONT:
        directionStr = "Forward";
        break;

    case BACK:
        directionStr = "Backwards";
        break;
    
    case FRONT_LEFT:
        directionStr = "Left-Forward";
        break;
    
    case FRONT_RIGHT:
        directionStr = "Right-Forward";
        break;
    
    case BACK_LEFT:
        directionStr = "Left-Backwards";
        break;
    
    case BACK_RIGHT:
        directionStr = "Right-Backwards";
        break;

    default:
        return false;
    
    return true;
    }

    std::cout << "Now driving: ";
};

void   TerrorByte::scanForTarget()
{
    //ToDo
}

bool   TerrorByte::isActive()
{
    return m_poweredON;
}

void  TerrorByte::measureDistance()
{
    int sensorPins[4];
    
    sensorPins[FRONT] = PIN_ULTRASONIC_SENSOR_FRONT;
    sensorPins[BACK]  = PIN_ULTRASONIC_SENSOR_BACK;
    sensorPins[LEFT]  = PIN_ULTRASONIC_SENSOR_LEFT;
    sensorPins[RIGHT] = PIN_ULTRASONIC_SENSOR_RIGHT;
    
    int *sensorData[4];

    sensorData[FRONT] = &m_spaceFrontSide;
    sensorData[BACK]  = &m_spaceBackSide;
    sensorData[LEFT]  = &m_spaceLeftSide;
    sensorData[RIGHT] = &m_spaceRightSide;

    for (int i = 0; i < 4; i++)
    {
        long duration = 0;

        pinMode(sensorPins[i], OUTPUT);
        digitalWrite(sensorPins[i], LOW);
        delayMicroseconds(2);
        digitalWrite(sensorPins[i], HIGH);
        delayMicroseconds(5);
        digitalWrite(sensorPins[i], LOW);

        pinMode(sensorPins[i], INPUT);
        duration = pulseIn(sensorPins[i], HIGH);

        *sensorData[i] = (duration / 29 / 2);
    }

};

void   TerrorByte::activateBuzzer(int hz, int duration)
{
    if (!duration)
    {
        tone(PIN_BUZZER, duration);
        return;
    }
    //else
    //{
        //ToDo
    //}
};

bool TerrorByte::beepingBuzzer(int hz, int duration, int sleepTime)
{
    //ToDo
};

void   TerrorByte::disableBuzzer()
{
    //This methode still needs to be implemented.
};

void TerrorByte::katapult()
{

};
