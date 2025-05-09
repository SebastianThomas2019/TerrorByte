#include "RgbLed.h"

RgbLed::RgbLed(const int PIN_RED, const int PIN_GREEN, const int PIN_BLUE):
    PIN_LED_RED(PIN_RED),
    PIN_LED_GREEN(PIN_GREEN),
    PIN_LED_BLUE(PIN_BLUE)
{
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_BLUE, OUTPUT);

    this->setColor(WHITE);
};

bool RgbLed::setColor(colors_t color)
{
    if (color == m_currentColor)
    {
        return false;
    }

    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_BLUE, LOW);

    switch (color)
    {
    case WHITE:
        digitalWrite(PIN_LED_GREEN, HIGH);
        digitalWrite(PIN_LED_BLUE, HIGH);
        digitalWrite(PIN_LED_RED, HIGH);
        m_currentColor = WHITE;
        break;
    
    case RED:
        digitalWrite(PIN_LED_RED, HIGH);
        m_currentColor = RED;
        break;
    
    case PINK:
        digitalWrite(PIN_LED_RED, HIGH);
        digitalWrite(PIN_LED_BLUE, HIGH);
        m_currentColor = PINK;
        break;
    
    case YELLOW:
        digitalWrite(PIN_LED_RED, HIGH);
        digitalWrite(PIN_LED_GREEN, HIGH);
        m_currentColor = YELLOW;
        break;
    
    case GREEN:
        digitalWrite(PIN_LED_GREEN, HIGH);
        m_currentColor = GREEN;
        break;
    
    case BLUE:
        digitalWrite(PIN_LED_BLUE, HIGH);
        m_currentColor = BLUE;
        break;
    
    default:
        return false;
        break;
    }

    return true;
};

RgbLed::colors_t   RgbLed::getColor()
{
    return m_currentColor;
};