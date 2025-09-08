#ifndef PINS
#define PINS


namespace pin 
{
    #ifdef MASTER
    const int RX_HUSKY = 0; // RX pin for HUSKYLENS
    const int TX_HUSKY = 1; // TX pin for HUSKYLENS
    const int CONTROLL_SLAVE_A = 2;
    const int MOTOR_FRONT_LEFT_PWM = 3;
    const int ULTRASONIC_LEFT_TRIGGER = 4;
    const int ULTRASONIC_LEFT_ECHO = 5;
    const int ULTRASONIC_RIGHT_TRIGGER = 6;
    const int ULTRASONIC_RIGHT_ECHO = 7;
    const int CONTROLL_SLAVE_B = 8;
    const int MOTOR_FRONT_LEFT_BRAKE = 9;
    const int MOTOR_FRONT_RIGHT_BRAKE = 10;
    const int MOTOR_FRONT_RIGHT_PWM = 11;
    const int MOTOR_FRONT_LEFT_DIRECTION = 12;
    const int MOTOR_FRONT_RIGHT_DIRECTION = 13;

    //Analog PINS
    const int POWER_SWITCH = A0;
    const int LED_BLUE = A1;
    const int LED_GREEN = A2;
    const int LED_RED = A3;
    const int LED_FRONT_AND_BACK = A4;
    const int CONTROLL_SLAVE_C = A5;
    #endif

    #ifdef SLAVE
    const int MASTER_CONTROLL_A = 0;
    const int MASTER_CONTROLL_B = 1;
    const int MASTER_CONTROLL_C = 2;
    const int MOTOR_BACK_LEFT_PWM = 3;
    const int MOTOR_BACK_LEFT_BRAKE = 9;
    const int MOTOR_BACK_RIGHT_BRAKE = 10;
    const int MOTOR_BACK_RIGHT_PWM = 11;
    const int MOTOR_BACK_LEFT_DIRECTION = 12;
    const int MOTOR_BACK_RIGHT_DIRECTION = 13;
    #endif
}




#endif