#ifndef RGBLED
#define RGBLED

#include <Arduino.h>

class RgbLed
{
public: 

    enum colors_t
    {
        WHITE,
        RED,
        PINK,
        YELLOW,
        GREEN,
        BLUE
    };

    RgbLed(const int PIN_RED, const int PIN_GREEN, const int PIN_BLUE);

    bool        setColor(colors_t color);
    colors_t    getColor();


private:
    const int   PIN_LED_RED;
    const int   PIN_LED_GREEN;
    const int   PIN_LED_BLUE;

    colors_t    m_currentColor;
};

#endif