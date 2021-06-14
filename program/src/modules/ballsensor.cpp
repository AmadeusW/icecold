#include "Arduino.h"
#include "ballsensor.h"
#include "../pins.h"

void BallSensor::Setup()
{
    pinMode(PinBallAtBottom, INPUT);
    pinMode(PinBallAtTarget, INPUT);

    Serial.println("Setup complete: BallSensor");
}

void BallSensor::Input()
{
    this->isBallDown = digitalRead(PinBallAtBottom) == HIGH;
    this->isBallOnTarget = digitalRead(PinBallAtTarget) == HIGH;
    // TODO: Record that ball was on target
    // next time the ball is down, we will score (instead of losing) and reset whether ball was on target
}

bool BallSensor::IsDown()
{
    return this->isBallDown;
}

bool BallSensor::IsOnTarget()
{
    return this->isBallOnTarget;
}
