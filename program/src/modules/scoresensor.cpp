#include "Arduino.h"
#include "scoresensor.h"
#include "../pins.h"

#define PinTarget 10
#define SensorScore 11

void ScoreSensor::Setup()
{
    pinMode(PinTarget, OUTPUT);
    pinMode(SensorScore, INPUT);
    this->SetTarget(false);
}

void ScoreSensor::Read()
{
    this->isBallDown = digitalRead(SensorBallDown) == HIGH;
    this->isBallOnTarget = digitalRead(SensorScore) == HIGH;
}

void ScoreSensor::SetTarget(bool enabled)
{
    if (enabled)
    {
        digitalWrite(PinTarget, HIGH);
    }
    else
    {
        digitalWrite(PinTarget, LOW);
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
