#include "Arduino.h"
#include "motor.h"
#include "../pins.h"

#define AIN1 1
#define AIN2 2
#define PWMA 3
#define STBY 0

void Motor::Setup()
{
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(STBY, OUTPUT);

    digitalWrite(STBY, HIGH);
}

void Motor::Read()
{
    // This module does not read any pins
}

void Motor::Brake()
{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
}

void Motor::Move(bool up, int speed)
{
    if (up)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);  
    }
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }
    analogWrite(PWMA, speed);
}
