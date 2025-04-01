#include "PID.h"
#include <gtest/gtest.h>

TEST(PIDTest, ZeroErrorReturnsZero) {
    PID pid(1.0, 1.0, 1.0);
    float output = pid.compute(0.0);
    EXPECT_FLOAT_EQ(output, 0.0);
}

TEST(PIDTest, ProportionalOnly) {
    PID pid(2.0, 0.0, 0.0);
    float output = pid.compute(5.0);
    EXPECT_FLOAT_EQ(output, 10.0);
}

TEST(PIDTest, IntegralOnly) {
    PID pid(0.0, 1.0, 0.0);
    float output1 = pid.compute(2.0); // integral = 2
    float output2 = pid.compute(2.0); // integral = 4
    EXPECT_FLOAT_EQ(output1, 2.0);
    EXPECT_FLOAT_EQ(output2, 4.0);
}

TEST(PIDTest, DerivativeOnly) {
    PID pid(0.0, 0.0, 1.0);
    pid.compute(3.0);                 // previousError = 3
    float output = pid.compute(6.0); // derivative = 3
    EXPECT_FLOAT_EQ(output, 3.0);
}

TEST(PIDTest, MixedPID) {
    PID pid(1.0, 0.5, 0.1);
    float output1 = pid.compute(4.0); // prevErr = 4, integral = 4
    float output2 = pid.compute(6.0); // prevErr = 6, integral = 10

    // output1 = 1*4 + 0.5*4 + 0.1*4 = 6.4
    // output2 = 1*6 + 0.5*10 + 0.1*2 = 11.2
    EXPECT_FLOAT_EQ(output1, 6.4);
    EXPECT_FLOAT_EQ(output2, 11.2);
}
