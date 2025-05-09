#ifndef TERRORBYTE
#define TERRORBYTE
# define EVER ;;

#include "RgbLed.h"
#include <Arduino.h>

class TerrorByte
{
public:
    enum direction_t
    {
        LEFT,
        RIGHT,
        FRONT,
        BACK,
        FRONT_LEFT,
        FRONT_RIGHT,
        BACK_LEFT,
        BACK_RIGHT
    };

    TerrorByte();

    void    powerButtonPressed();
    void    getDistances(int array[4]);
    bool    driveInDirection(direction_t direction);
    void    scanForTarget();
    bool    isActive();

private:
    void    measureDistance();
    void    activateBuzzer(int hz, int duration = 0);
    bool    beepingBuzzer(int hz, int duration, int sleepTime);
    void    disableBuzzer();

    const int DURATION_FOR_MOVEMENT = 3; // seconds
    const int FREQUENZ_BUZZER_DRIVING_BACKWARDS = 950; //Hz
    const int PIN_ULTRASONIC_SENSOR_LEFT = 6;
    const int PIN_ULTRASONIC_SENSOR_RIGHT = 7;
    const int PIN_ULTRASONIC_SENSOR_FRONT = 8;
    const int PIN_ULTRASONIC_SENSOR_BACK = 12;
    const int PIN_LEDS_FRONT = 5;
    const int PIN_LEDS_BACK = 4;
    const int PIN_BUZZER = 13;

    RgbLed     *ptr_statusRgb;
    bool        m_poweredON;
    int         m_spaceLeftSide;
    int         m_spaceRightSide;
    int         m_spaceFrontSide;
    int         m_spaceBackSide;
};
#endif
