#include "Arduino.h"
#include "scoresensor.h"
#include "../pins.h"

void ScoreSensor::Setup()
{
    pinMode(PinBallAtBottom, INPUT);
    pinMode(PinBallAtTarget, INPUT);
    this->SetTarget(false);

    Serial.println("Setup complete: ScoreSensor");
}

void ScoreSensor::Read()
{
    this->isBallDown = digitalRead(PinBallAtBottom) == HIGH;
    this->isBallOnTarget = digitalRead(PinBallAtTarget) == HIGH;
    // TODO: Record that ball was on target
    // next time the ball is down, we will score (instead of losing) and reset whether ball was on target
}

void ScoreSensor::SetTarget(bool enabled)
{
    // Obsolete prototype
    if (enabled)
    {
        //digitalWrite(PinTarget, HIGH);
    }
    else
    {
        //digitalWrite(PinTarget, LOW);
    }
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
