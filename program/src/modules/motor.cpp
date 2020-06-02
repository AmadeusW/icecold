#include "Arduino.h"
#include "motor.h"
#include "../pins.h"

void Motor::Setup()
{
    pinMode(PinMotorAIn1, OUTPUT);
    pinMode(PinMotorAIn2, OUTPUT);
    pinMode(PinMotorPWMA, OUTPUT);
    pinMode(PinMotorSTBY, OUTPUT);

    digitalWrite(PinMotorSTBY, HIGH);

    Serial.println("Setup complete: Motor");
}

void Motor::Read()
{
    // This module does not read any pins
}

void Motor::Brake()
{
    digitalWrite(PinMotorAIn1, HIGH);
    digitalWrite(PinMotorAIn2, HIGH);
}

void Motor::Move(bool up, int speed)
{
    if (up)
    {
        digitalWrite(PinMotorAIn1, HIGH);
        digitalWrite(PinMotorAIn2, LOW);  
    }
    else
    {
        digitalWrite(PinMotorAIn1, LOW);
        digitalWrite(PinMotorAIn2, HIGH);
    }
    analogWrite(PinMotorPWMA, speed);
}
