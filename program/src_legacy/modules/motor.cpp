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

void Motor::Output(int tick)
{
    if (this->speedLeft == 0)
    {
        digitalWrite(PinMotorAIn1, HIGH);
        digitalWrite(PinMotorAIn2, HIGH);
    }
    else if (this->speedLeft > 0)
    {
        digitalWrite(PinMotorAIn1, HIGH);
        digitalWrite(PinMotorAIn2, LOW); 
        analogWrite(PinMotorPWMA, this->speedLeft);
    }
    else
    {
        digitalWrite(PinMotorAIn1, LOW);
        digitalWrite(PinMotorAIn2, HIGH); 
        analogWrite(PinMotorPWMA, -(this->speedLeft));
    }

    if (this->speedRight == 0)
    {
        digitalWrite(PinMotorBIn1, HIGH);
        digitalWrite(PinMotorBIn2, HIGH);
    }
    else if (this->speedRight > 0)
    {
        digitalWrite(PinMotorBIn1, HIGH);
        digitalWrite(PinMotorBIn2, LOW); 
        analogWrite(PinMotorPWMB, this->speedRight);
    }
    else
    {
        digitalWrite(PinMotorBIn1, LOW);
        digitalWrite(PinMotorBIn2, HIGH); 
        analogWrite(PinMotorPWMB, -(this->speedRight));
    }
}

void Motor::Brake()
{
    this->speedLeft = 0;
    this->speedRight = 0;
}

void Motor::MoveLeft(bool up, int speed)
{
    this->speedLeft = up ? speed : -speed;
}

void Motor::MoveRight(bool up, int speed)
{
    this->speedRight = up ? speed : -speed;
}
