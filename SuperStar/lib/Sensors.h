#ifndef SENSORS_H
#define SENSORS_H

#include <NewPing.h>
#include <Servo.h>

class Sensors {
public:
    Sensors(int irLeft, int irRight, int trig, int echo, int servoPin);
    int readIRLeft();
    int readIRRight();
    int readDistance();
    void scanObstacle();
private:
    int IR_LEFT, IR_RIGHT;
    NewPing distanceSensor;
    Servo servo;
    int servoPosition;
};

#endif
