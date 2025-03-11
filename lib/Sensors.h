#ifndef SENSORS_H
#define SENSORS_H

#include <NewPing.h>
#include <Servo.h>

class Sensors {
public:
    Sensors(int irLeftPin, int irRightPin, int trigPin, int echoPin, int servoPin);
    int readIRLeft();
    int readIRRight();
    int readDistance();
    void setServoAngle(int angle);
private:
    int IR_LEFT, IR_RIGHT;
    NewPing distanceSensor;
    Servo servo;
};

#endif
