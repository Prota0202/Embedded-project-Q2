#include "PID.h"

PID::PID(float kp, float ki, float kd) :
    kp(kp), ki(ki), kd(kd), previousError(0), integral(0) {}

float PID::compute(float error) {
    integral += error;
    float derivative = error - previousError;
    previousError = error;
    return kp * error + ki * integral + kd * derivative;
}
