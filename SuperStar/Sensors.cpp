#include "Sensors.h"
#include <Arduino.h>

Sensors::Sensors(int irLeft, int irRight, int trig, int echo, int servoPin)
    : IR_LEFT(irLeft), IR_RIGHT(irRight), distanceSensor(trig, echo, 200) {
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_RIGHT, INPUT);
    servo.attach(servoPin);
    servo.write(90);
}

int Sensors::readIRLeft() {
    return analogRead(IR_LEFT);
}

int Sensors::readIRRight() {
    return analogRead(IR_RIGHT);
}

int Sensors::readDistance() {
    return distanceSensor.ping_cm();
}

void Sensors::scanObstacle() {
    servo.write(45);
    delay(500);
    int leftDist = readDistance();
    
    servo.write(135);
    delay(500);
    int rightDist = readDistance();

    servo.write(90);
}
