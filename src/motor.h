#ifndef MOTOR
#define MOTOR

class Motor
{
public:

    enum Direction
    {
        LEFT,
        RIGHT,
        STOP
    };

    Motor(const int pwmPin, const int directionPin, const int brakePin);
    ~Motor();

    void turnLeft();
    void turnRight();
    void stop();

private:
    const int SPEED = 200; // Speed of the motor, can be adjusted

    int m_pwmPin;
    int m_directionPin;
    int m_brakePin;
    Direction m_direction; // Current direction of the motor

};

#endif