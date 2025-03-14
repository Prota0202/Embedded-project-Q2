#ifndef PID_H
#define PID_H

class PID {
public:
    PID(float kp, float ki, float kd);
    float compute(float error);
private:
    float kp, ki, kd;
    float previousError, integral;
};

#endif
