#include "Arduino.h"
#include "scoresensor.h"
#include "../pins.h"

void ScoreSensor::Setup()
{
    pinMode(PinBallAtBottom, INPUT);
    pinMode(PinBallAtTarget, INPUT);

    Serial.println("Setup complete: ScoreSensor");
}

void ScoreSensor::Input()
{
    this->isBallDown = digitalRead(PinBallAtBottom) == HIGH;
    this->isBallOnTarget = digitalRead(PinBallAtTarget) == HIGH;
    // TODO: Record that ball was on target
    // next time the ball is down, we will score (instead of losing) and reset whether ball was on target

    // TODO: Set state
}

bool ScoreSensor::IsScoring()
{
    return this->isBallOnTarget;
}

bool ScoreSensor::IsLosing()
{
    // TODO: this is more nuanced. We are losing only if ball is down and we have not scored
    return this->isBallDown;
}
