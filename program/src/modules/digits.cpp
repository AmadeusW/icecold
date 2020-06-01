#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "digits.h"
#include "../pins.h"

Adafruit_7segment matrix = Adafruit_7segment();

void Digits::Setup()
{
    pinMode(PinI2CClock, OUTPUT);
    pinMode(PinI2CData, OUTPUT);
    matrix.begin(0x70);
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
    matrix.print(this->value);
    matrix.writeDisplay();
}
