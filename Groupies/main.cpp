#include <Arduino.h>
#include "../lib/Motors.h"
#include "../lib/Sensors.h"
#include "../lib/PID.h"

// Pins definitions
#define IR_LEFT A0
#define IR_RIGHT A1
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 4

// Initialisations
Motors motors;
Sensors sensors(IR_LEFT, IR_RIGHT, TRIGGER_PIN, ECHO_PIN, SERVO_PIN);
PID pidController(1.5, 0.0, 0.5);

unsigned long startTime;
const unsigned long runDuration = 10000;
const int baseSpeed = 50;
const int obstacleThreshold = 15;

void setup() {
    Serial.begin(9600);
    delay(5000);
    startTime = millis();
}

void loop() {
    if (millis() - startTime >= runDuration) {
        motors.stop();
        Serial.println("Automatic stop after 10 seconds");
        while (true);
    }

    int distance = sensors.readDistance();
    if (distance > 0 && distance <= obstacleThreshold) {
        motors.stop();
        motors.moveBackward(baseSpeed, 500);
        motors.stop();

        sensors.setServoAngle(45);
        int L = sensors.readDistance();
        sensors.setServoAngle(135);
        int R = sensors.readDistance();
        sensors.setServoAngle(90);

        if (L < R) motors.turnRight(baseSpeed, 500);
        else motors.turnLeft(baseSpeed, 500);
        return;
    }

    int valueLeft = sensors.readIRLeft();
    int valueRight = sensors.readIRRight();
    float correction = pidController.compute(valueRight - valueLeft);

    int speedLeft = constrain(baseSpeed - correction, 0, 50);
    int speedRight = constrain(baseSpeed + correction, 0, 50);

    motors.moveForward(min(speedLeft, speedRight));
    delay(10);
}
