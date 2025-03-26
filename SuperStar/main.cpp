#include "../Motors.h"
#include "../Sensors.h"
#include "../PID.h"
#include <Arduino.h>

// Pins
#define IR_LEFT A0
#define IR_RIGHT A1
#define IR_CLIFF A2
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 3

Motors motors;
Sensors sensors(IR_LEFT, IR_RIGHT, IR_CLIFF,TRIGGER_PIN, ECHO_PIN, SERVO_PIN);
PID pidController(1.5, 0.0, 0.5);

const int obstacleThreshold = 15;
const int cliffThreshold = 600;

void setup() {
    Serial.begin(9600);
    delay(500);
}

void loop() {
    int distance = sensors.readDistance();
    int cliffValue = sensors.readIRCliff();

    if (distance > 0 && distance <= obstacleThreshold) {
        motors.stop();
        motors.backward();
        delay(500);
        motors.stop();
        return;
    }
    
    if (cliffValue > cliffThreshold) {
        motors.stop();
        motors.backward();
        delay(500);
        motors.stop();
        return;
    }

    int valueLeft = sensors.readIRLeft();
    int valueRight = sensors.readIRRight();
    float correction = pidController.compute(valueRight - valueLeft);

    int speedLeft = constrain(100 - correction, 0, 100);
    int speedRight = constrain(100 + correction, 0, 100);

    motors.forward();
    delay(10);
}
