#ifndef SENSORS_H
#define SENSORS_H

#include <NewPing.h>
#include <Servo.h>

class Sensors {
public:
    Sensors(int irLeft, int irRight, int irCliff, int trig, int echo, int servoPin);
    int readIRLeft();
    int readIRRight();
    int readIRCliff();
    int readDistance();
    void scanObstacle();
private:
    int IR_LEFT, IR_RIGHT, IR_CLIFF;
    NewPing distanceSensor;
    Servo servo;
    int servoPosition;
};

#endif
