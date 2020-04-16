#include "Arduino.h"
#include "scoresensor.h"
#include "../pins.h"

void ScoreSensor::setup()
{
    // TODO: Set Pins
    this->setTarget(false);
}

void ScoreSensor::setTarget(bool enabled)
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

// TODO: Read Pins

bool ScoreSensor::isScoring()
{
    return digitalRead(SensorScore);
}
