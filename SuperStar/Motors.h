#ifndef MOTORS_H
#define MOTORS_H

#include <Adafruit_MotorShield.h>

class Motors {
public:
    Motors();
    void init();
    void forward(int speed = 150);
    void backward(int speed = 150);
    void right(int speed = 150);
    void left(int speed = 150);
    void stop();
    
    // Rendre les moteurs publics
    Adafruit_DCMotor* motorLEFT;   // Déclaration publique
    Adafruit_DCMotor* motorRIGHT;  // Déclaration publique

private:
    Adafruit_MotorShield AFMS;
};

#endif