#include "Motors.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

class MockMotor : public Adafruit_DCMotor {
public:
    MOCK_METHOD(void, setSpeed, (uint8_t), (override));
    MOCK_METHOD(void, run, (uint8_t), (override));
};

class MockShield : public Adafruit_MotorShield {
public:
    MockMotor* left = new MockMotor();
    MockMotor* right = new MockMotor();

    void begin() override {}
    Adafruit_DCMotor* getMotor(uint8_t n) override {
        return (n == 3) ? left : right;
    }
};

class TestableMotors : public Motors {
public:
    TestableMotors(MockShield* shield) {
        AFMS = *shield;
        motorLEFT = shield->left;
        motorRIGHT = shield->right;
    }
};

TEST(MotorsTest, Forward) {
    MockShield shield;
    TestableMotors motors(&shield);

    EXPECT_CALL(*shield.left, setSpeed(100));
    EXPECT_CALL(*shield.right, setSpeed(100));
    EXPECT_CALL(*shield.left, run(FORWARD));
    EXPECT_CALL(*shield.right, run(FORWARD));

    motors.forward(100);
}
