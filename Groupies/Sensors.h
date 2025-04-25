#ifndef SENSORS_H
#define SENSORS_H

#include <NewPing.h>
#include <Servo.h>

class Sensors {
public:
    Sensors(int irLeft, int irRight, int irCliff, int trig1, int echo1, int trig2, int echo2, int servoPin);
    int readIRLeft();
    int readIRRight();
    int readIRCliff();
    int readDistance1();
    int readDistance2();
    void initServo();
    void setServoAngle(int angle);
private:
    int IR_LEFT, IR_RIGHT, IR_CLIFF;
    NewPing distanceSensor1;
    NewPing distanceSensor2;
    Servo servo;
    int servoPin;
};

#endif