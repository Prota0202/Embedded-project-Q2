#include "Sensors.h"
#include <Arduino.h>

Sensors::Sensors(int irLeft, int irRight, int irCliff, int trig1, int echo1, int trig2, int echo2, int servoPin)
    : IR_LEFT(irLeft), IR_RIGHT(irRight), IR_CLIFF(irCliff), 
      distanceSensor1(trig1, echo1, 200),
      distanceSensor2(trig2, echo2, 200) {
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_RIGHT, INPUT);
    pinMode(IR_CLIFF, INPUT);
    servo.attach(servoPin);
    servo.write(90);
}

int Sensors::readIRLeft() {
    return analogRead(IR_LEFT);
}

int Sensors::readIRRight() {
    return analogRead(IR_RIGHT);
}

int Sensors::readIRCliff() {
    return analogRead(IR_CLIFF);
}

int Sensors::readDistance1() {
    return distanceSensor1.ping_cm();
}

int Sensors::readDistance2() {
    return distanceSensor2.ping_cm();
}

void Sensors::scanObstacle() {
    servo.write(45);
    delay(500);
    int leftDist = readDistance1();
    
    servo.write(135);
    delay(500);
    int rightDist = readDistance1();

    servo.write(90);
}