#include "motor.h"
#include <Arduino.h>

Motor::Motor(const int pwmPin, const int directionPin, const int brakePin)
    : m_pwmPin(pwmPin), m_directionPin(directionPin), m_brakePin(brakePin), m_direction(STOP)
{
    pinMode(m_directionPin, OUTPUT);
    pinMode(m_pwmPin, OUTPUT);
    pinMode(m_brakePin, OUTPUT);
};

Motor::~Motor()
{

};

void Motor::turnLeft()
{
    if(m_direction != LEFT) {
        m_direction = LEFT;
        digitalWrite(m_brakePin, LOW); // Release brake
        digitalWrite(m_directionPin, LOW);
        for (int x = 0; x < SPEED; x++)
        {
            analogWrite(m_pwmPin, x); // Set speed
            delay(5);
        }
    }
};

void Motor::turnRight()
{
    if(m_direction != RIGHT) {
        m_direction = RIGHT;
        digitalWrite(m_brakePin, LOW); // Release brake
        digitalWrite(m_directionPin, HIGH);
        for (int x = 0; x < SPEED; x++)
        {
            analogWrite(m_pwmPin, x); // Set speed
            delay(5);
        }
    }
};

void Motor::stop()
{
    if(m_direction != STOP) {
        m_direction = STOP;
        digitalWrite(m_directionPin, LOW);
        for (int x = SPEED; x > 0; x--)
        {
            analogWrite(m_pwmPin, x); // Stop the motor
            delay(5);
        }
        digitalWrite(m_brakePin, HIGH); // Engage brake        
    }
};
