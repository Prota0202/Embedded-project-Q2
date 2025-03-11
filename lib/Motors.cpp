#include "Motors.h"
#include <Arduino.h>

Motors::Motors() : AFMS(), motorLEFT(AFMS.getMotor(1)), motorRIGHT(AFMS.getMotor(2)) {
    AFMS.begin();
}

void Motors::moveForward(int speed, int duration) {
    motorLEFT->setSpeed(speed);
    motorRIGHT->setSpeed(speed);
    motorLEFT->run(BACKWARD);
    motorRIGHT->run(BACKWARD);
    if (duration > 0) delay(duration);
}

void Motors::moveBackward(int speed, int duration) {
    motorLEFT->setSpeed(speed);
    motorRIGHT->setSpeed(speed);
    motorLEFT->run(FORWARD);
    motorRIGHT->run(FORWARD);
    if (duration > 0) delay(duration);
}

void Motors::turnLeft(int speed, int duration) {
    motorLEFT->setSpeed(speed);
    motorRIGHT->setSpeed(speed);
    motorLEFT->run(FORWARD);
    motorRIGHT->run(BACKWARD);
    delay(duration);
    stop();
}

void Motors::turnRight(int speed, int duration) {
    motorLEFT->setSpeed(speed);
    motorRIGHT->setSpeed(speed);
    motorLEFT->run(BACKWARD);
    motorRIGHT->run(FORWARD);
    delay(duration);
    stop();
}

void Motors::stop() {
    motorLEFT->setSpeed(0);
    motorRIGHT->setSpeed(0);
    motorLEFT->run(RELEASE);
    motorRIGHT->run(RELEASE);
}
