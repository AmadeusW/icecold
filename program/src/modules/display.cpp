#include "Arduino.h"
#include "display.h"
#include "../pins.h"

#define PinSerialClock 8
#define PinSerialClearNot 9
#define PinSerialInput 12

void Display::Setup()
{
    pinMode(PinSerialClock, OUTPUT);
    pinMode(PinSerialClearNot, PinSerialClearNot);
    this->SetScore(0);
}

void Display::Read()
{
    // This module does not read any pins
}

void Display::SetScore(int score)
{
    this->score = score;
}

void Display::Write()
{
    digitalWrite(PinSerialClearNot, 0); // Clear
    delay(1);
    digitalWrite(PinSerialClock, 0);
    digitalWrite(PinSerialClearNot, 1);
    digitalWrite(PinSerialInput, this->score > 0);
    digitalWrite(PinSerialClock, 1);
    delay(1);
    digitalWrite(PinSerialClock, 0);
    digitalWrite(PinSerialInput, this->score > 1);
    digitalWrite(PinSerialClock, 1);
    delay(1);
    digitalWrite(PinSerialClock, 0);
    digitalWrite(PinSerialInput, this->score > 2);
    digitalWrite(PinSerialClock, 1);
    delay(1);
    digitalWrite(PinSerialClock, 0);
    digitalWrite(PinSerialInput, this->score > 3);
    digitalWrite(PinSerialClock, 1);
    delay(1);
    digitalWrite(PinSerialClock, 0);
    digitalWrite(PinSerialInput, this->score > 4);
    digitalWrite(PinSerialClock, 1);
}
