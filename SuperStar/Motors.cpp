#include "Motors.h"

Motors::Motors() : AFMS(), motorLEFT(AFMS.getMotor(3)), motorRIGHT(AFMS.getMotor(4)) {
    AFMS.begin();
}

void Motors::forward() {
    motorLEFT->setSpeed(100);
    motorRIGHT->setSpeed(100);
    motorLEFT->run(FORWARD);
    motorRIGHT->run(FORWARD);
}

void Motors::backward() {
    motorLEFT->setSpeed(100);
    motorRIGHT->setSpeed(100);
    motorLEFT->run(BACKWARD);
    motorRIGHT->run(BACKWARD);
}

void Motors::right() {
    motorLEFT->setSpeed(100);
    motorRIGHT->setSpeed(100);
    motorLEFT->run(FORWARD);
    motorRIGHT->run(BACKWARD);
}

void Motors::left() {
    motorLEFT->setSpeed(100);
    motorRIGHT->setSpeed(100);
    motorLEFT->run(BACKWARD);
    motorRIGHT->run(FORWARD);
}

void Motors::stop() {
    motorLEFT->setSpeed(0);
    motorRIGHT->setSpeed(0);
    motorLEFT->run(RELEASE);
    motorRIGHT->run(RELEASE);
}
