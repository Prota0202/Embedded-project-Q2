#include "Motors.h"

Motors::Motors() : AFMS() {
    
}

void Motors::init() {
    AFMS.begin();
    motorLEFT = AFMS.getMotor(3);
    motorRIGHT = AFMS.getMotor(4);
}

void Motors::backward(int speed) {
    motorLEFT->setSpeed(speed);
    motorRIGHT->setSpeed(speed);
    motorLEFT->run(FORWARD);
    motorRIGHT->run(FORWARD);
}

void Motors::forward(int speed) {
    motorLEFT->setSpeed(speed);
    motorRIGHT->setSpeed(speed);
    motorLEFT->run(BACKWARD);
    motorRIGHT->run(BACKWARD);
}

void Motors::right(int speed) {
    motorLEFT->setSpeed(speed);
    motorRIGHT->setSpeed(speed);
    motorLEFT->run(BACKWARD);
    motorRIGHT->run(FORWARD);
}

void Motors::left(int speed) {
    motorLEFT->setSpeed(speed);
    motorRIGHT->setSpeed(speed);
    motorLEFT->run(FORWARD);
    motorRIGHT->run(BACKWARD);
}

void Motors::stop() {
    motorLEFT->run(RELEASE);
    motorRIGHT->run(RELEASE);
}