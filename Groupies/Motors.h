#ifndef MOTORS_H
#define MOTORS_H

#include <Adafruit_MotorShield.h>

class Motors {
public:
    Motors();
    void moveForward(int speed, int duration = 0);
    void moveBackward(int speed, int duration = 0);
    void turnLeft(int speed, int duration);
    void turnRight(int speed, int duration);
    void stop();
private:
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor *motorLEFT;
    Adafruit_DCMotor *motorRIGHT;
};

#endif
