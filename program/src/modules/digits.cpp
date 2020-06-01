#include "Arduino.h"
#include "digits.h"
#include "../pins.h"

void Digits::Setup()
{
    pinMode(PinI2CClock, OUTPUT);
    pinMode(PinI2CData, OUTPUT);
    this->Write();
}

void Digits::Read()
{
    // This module does not read any pins
}

void Digits::SetValue(int value)
{
    this->value = value;
}

void Digits::Write()
{
    
}
