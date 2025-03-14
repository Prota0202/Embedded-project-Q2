#ifndef MOTORS_H
#define MOTORS_H

#include <Adafruit_MotorShield.h>

class Motors {
public:
    Motors();
    void forward();
    void backward();
    void right();
    void left();
    void stop();
private:
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor *motorLEFT;
    Adafruit_DCMotor *motorRIGHT;
};

#endif
