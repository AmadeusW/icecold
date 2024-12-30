#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "digits.h"
#include "../pins.h"

void Digits::Setup()
{
    pinMode(PinI2CClock, OUTPUT);
    pinMode(PinI2CData, OUTPUT);
    this->matrix = new Adafruit_7segment();
    this->matrix->begin(0x70);

    this->SetValue(0);
    this->Output(0);

    Serial.println("Setup complete: Digits");
}

void Digits::SetValue(int value)
{
    this->value = value;
}

void Digits::Output(int tick)
{
    this->matrix->print(this->value);
    this->matrix->writeDisplay();
}
