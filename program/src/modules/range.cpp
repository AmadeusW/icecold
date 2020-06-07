#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include "range.h"
#include "../pins.h"

VL53L0X lox0;
VL53L0X lox1;

void Range::Setup()
{
    this->value0 = 0;
    this->initialized0 = false;
    this->value1 = 0;
    this->initialized1 = false;
    pinMode(PinI2CClock, OUTPUT);
    pinMode(PinI2CData, OUTPUT);
    pinMode(PinRange0Enable, OUTPUT);
    pinMode(PinRange1Enable, OUTPUT);
    // Program freezes if we initialize without the call to Wire.begin
    Wire.begin();

    lox0.setTimeout(100);
    lox1.setTimeout(100);
    // Shut off sensors
    digitalWrite(PinRange0Enable, 0);
    delay(10);
    digitalWrite(PinRange1Enable, 0);
    delay(10);

    // Enable one sensor and adjust its address
    digitalWrite(PinRange0Enable, 1);
    delay(10);
    lox0.setAddress(0x28); // it's 0x29 by default
    if (lox0.init())
    {
        Serial.println("Setup complete: Range 0");
        this->initialized0 = true;
    }
    else
    {
        this->initialized0 = false;
        Serial.println("Error: Setup failed: Range 0");
    }

    digitalWrite(PinRange1Enable, 1);
    delay(10);
    if (lox1.init())
    {
        this->initialized1 = true;
        Serial.println("Setup complete: Range 1");
    }
    else
    {
        this->initialized1 = false;
        Serial.println("Error: Setup failed: Range 1");
    }

    uint8_t a0 = lox0.getAddress();
    uint8_t a1 = lox1.getAddress();
    Serial.printf("Address0: %x --- Address1: %x \n", a0, a1);
}

void Range::Read()
{
    if (this->initialized0)
    {
        this->value0 = lox0.readRangeSingleMillimeters();
        if (lox0.timeoutOccurred())
        {
            Serial.println("Range 0 timed out.");
        }
        else
        {
            Serial.printf("Range0 %d \n", this->value0);
        }
    }
    if (this->initialized1)
    {
        this->value1 = lox1.readRangeSingleMillimeters();
        if (lox1.timeoutOccurred())
        {
            Serial.println("Range 1 timed out.");
        }
        else
        {
            Serial.printf("Range1 %d \n", this->value1);
        }
    }
}

int Range::GetValue(int module)
{
    switch (module)
    {
        case 0:
            return this->value0;
        case 1:
            return this->value1;
        default:
            return 0;
    }
}
