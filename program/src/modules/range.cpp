#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include "range.h"
#include "../pins.h"

VL53L0X lox;

void Range::Setup()
{
    pinMode(PinI2CClock, OUTPUT);
    pinMode(PinI2CData, OUTPUT);
    pinMode(PinRange1Enable, OUTPUT);
    // Program freezes if we initialize without the call to Wire.begin
    Wire.begin();

    lox.setTimeout(100);
    // Reset sensors
    digitalWrite(PinRange1Enable, 0);
    delay(10);
    digitalWrite(PinRange1Enable, 1);
    delay(10);

    if (!lox.init())
    {
        Serial.println("Error: Setup failed: Range");
    }
    else
    {
        Serial.println("Setup complete: Range");
    }
    
}

void Range::Read()
{
    this->value = lox.readRangeSingleMillimeters();
    if (lox.timeoutOccurred())
    {
        Serial.print("Timeout occured, but here's the value: ");
    }
    Serial.println(this->value);
}

int Range::GetValue()
{
    return this->value;
}
