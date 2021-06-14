#include "Arduino.h"
#include "joystick.h"
#include "../pins.h"

void Joystick::Setup()
{
    pinMode(PinJoyAUp, INPUT);
    pinMode(PinJoyADown, INPUT);
    pinMode(PinJoyBUp, INPUT);
    pinMode(PinJoyBDown, INPUT);

    Serial.println("Setup complete: Joystick");
}

void Joystick::Input()
{
    this->leftDirection = digitalRead(PinJoyAUp) == HIGH ? 1 : 0;
    this->leftDirection += digitalRead(PinJoyADown) == HIGH ? -1 : 0;
    this->rightDirection = digitalRead(PinJoyBUp) == HIGH ? 1 : 0;
    this->rightDirection += digitalRead(PinJoyBDown) == HIGH ? -1 : 0;
}

int Joystick::GetLeftDirection()
{
    return this->leftDirection;
}

int Joystick::GetRightDirection()
{
    return this->rightDirection;
}
