#include "Motors.h"
#include "Sensors.h"
#include "PID.h"
#include <Arduino.h>

// Pins
#define IR_LEFT A0
#define IR_RIGHT A1
#define TRIGGER_PIN1 1
#define ECHO_PIN1 0
#define TRIGGER_PIN2 2
#define ECHO_PIN2 3
#define SERVO_PIN 6
#define SWITCH_PIN 7
#define MAGNET_PIN 4

Motors motors;
Sensors sensors(IR_LEFT, IR_RIGHT, -1, TRIGGER_PIN1, ECHO_PIN1, TRIGGER_PIN2, ECHO_PIN2, SERVO_PIN); // -1 for unused cliff sensor
PID pidController(1.5, 0.0, 0.5);

const int obstacleThreshold = 5;

// Variable to check if the robot is permanently stopped
bool isStopped = false;

bool danceTime = false;

bool robotStarted = false;

// Variables to manage runtime
unsigned long startTime;
const unsigned long maxRunTime = 5400; // 10 seconds in milliseconds

void setup() {
    Serial.begin(9600);

    pinMode(MAGNET_PIN, INPUT_PULLUP);

    pinMode(SWITCH_PIN, INPUT_PULLUP); // Switch between pin and GND
    motors.init();
    Serial.println("Robot ready");
    sensors.initServo();
}

void loop() {

    // Check the magnetic sensor
    if (!robotStarted) {
        if (digitalRead(MAGNET_PIN) == HIGH) {
            // Magnet has been removed, start the robot
            Serial.println("Magnet removed! Starting robot...");

            // DELAY BEFORE START AFTER STRING PULL

            delay(85000);

            robotStarted = true;
            startTime = millis();  // Initialize start time now
            delay(1000);  // Small delay to avoid bouncing
        } else {
            // Magnet is still present, do nothing
            delay(100);  // Small pause to avoid CPU overload
            return;
        }
    }

    // If the robot hasn't started yet, exit
    if (!robotStarted) {
        return;
    }

    if (isStopped) {
        return;
    }

    if (millis() - startTime >= maxRunTime) {
        Serial.println("Maximum runtime reached");
        // Read the switch state
        bool switchState = digitalRead(SWITCH_PIN) == LOW; // OFF = true, ON = false
        if (switchState) {
            Serial.println("End of run: switch is OFF → Turning left");
            motors.left(50);
        } else {
            Serial.println("End of run: switch is ON → Turning right");
            motors.right(50);
        }
        delay(500); // Turn for 0.5 seconds
        motors.forward(50);
        delay(1200); // Move forward for 1.2 seconds
        motors.stop();

        // Perform the dance here before setting isStopped to true
        Serial.println("Dance mode activated!");
        unsigned long danceStartTime = millis(); // Record dance start time
        while (millis() - danceStartTime < 10000) { // Dance for 10 seconds
            sensors.setServoAngle(0); // Move servo to 0°
            delay(300); // Wait 300ms
            sensors.setServoAngle(180); // Move servo to 180°
            delay(300); // Wait 300ms
            sensors.setServoAngle(90); // Return servo to 90°
            delay(200); // Wait 200ms
        }
        Serial.println("Dance mode ended");

        // Now stop the robot permanently
        isStopped = true;
        return;
    }

    bool switchState = digitalRead(SWITCH_PIN) == LOW; //OFF yellow side, ON blue side
    int distance;

    // If switch is ON → sensor 2 active
    if (switchState) {
        distance = sensors.readDistance2();
        Serial.println("Ultrasonic sensor active: 2");
    } else {
        distance = sensors.readDistance1();
        Serial.println("Ultrasonic sensor active: 1");
    }

    if (distance > 0 && distance <= obstacleThreshold) {
        Serial.println("Obstacle detected");
        motors.stop();
        motors.backward(100);
        delay(500);
        motors.stop();
        delay(500);
        return;
    }

    // PID for trajectory correction
    int valueLeft = sensors.readIRLeft();
    int valueRight = sensors.readIRRight();
    float correction = pidController.compute(valueRight - valueLeft);
    int speedLeft = constrain(60 - correction, 0, 60);
    int speedRight = constrain(60 + correction, 0, 60);
    motors.forward();
    motors.motorLEFT->setSpeed(speedLeft);
    motors.motorRIGHT->setSpeed(speedRight);
    delay(10);
}