#include "Sensors.h"
#include <Arduino.h>

Sensors::Sensors(int irLeftPin, int irRightPin, int trigPin, int echoPin, int servoPin)
    : IR_LEFT(irLeftPin), IR_RIGHT(irRightPin), distanceSensor(trigPin, echoPin, 200) {
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

void Sensors::setServoAngle(int angle) {
    servo.write(angle);
    delay(500);
}
