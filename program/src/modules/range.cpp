#include <Arduino.h>
#include <VL53L0X.h>
#include <Wire.h>
#include "range.h"
#include "../pins.h"

VL53L0X lox;

void Range::Setup()
{
    pinMode(PinI2CClock, OUTPUT);
    pinMode(PinI2CData, OUTPUT);
    pinMode(PinRange1Enable, OUTPUT);
    Wire.begin();

    //this->sensor = new VL53L0X();
    //this->sensor->setTimeout(100);
    lox.setTimeout(100);
/*
    // Reset sensors
    digitalWrite(PinRange1Enable, 0);
    delay(10);
    digitalWrite(PinRange1Enable, 1);
    delay(10);
*/
    if (!lox.init())
    //if (!(this->sensor->init(/*io_2v8*/ true)))
    {
        Serial.println("Error: Setup failed: Range");
        // TODO: have a better indicator of what failed
    }
    else
    {
        Serial.println("Setup complete: Range");
    }
    
}

void Range::Read()
{
    Serial.println("Begin read");
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
