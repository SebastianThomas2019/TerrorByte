// #ifndef TERRORBYTE
// #define TERRORBYTE
// # define EVER ;;

// #include "RgbLed.h"
// #include <Arduino.h>

// class TerrorByte
// {
// public:
//     enum direction_t
//     {
//         LEFT,
//         RIGHT,
//         FRONT,
//         BACK,
//         FRONT_LEFT,
//         FRONT_RIGHT,
//         BACK_LEFT,
//         BACK_RIGHT
//     };

//     TerrorByte();

//     void    powerButtonPressed();
//     void    getDistances(int array[4]);
//     bool    driveInDirection(direction_t direction);
//     void    scanForTarget();
//     bool    isActive();
//     void    katapult();

// private:
//     void    measureDistance();
//     void    activateBuzzer(int hz, int duration = 0);
//     bool    beepingBuzzer(int hz, int duration, int sleepTime);
//     void    disableBuzzer();

//     const int DURATION_FOR_MOVEMENT = 3; // seconds
//     const int FREQUENZ_BUZZER_DRIVING_BACKWARDS = 950; //Hz

//     RgbLed     *ptr_statusRgb;
//     bool        m_poweredON;
//     int         m_spaceLeftSide;
//     int         m_spaceRightSide;
//     int         m_spaceFrontSide;
//     int         m_spaceBackSide;
// };
// #endif
