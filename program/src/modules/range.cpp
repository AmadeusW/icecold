#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include "range.h"
#include "../pins.h"

VL53L0X lox0;
VL53L0X lox1;

void Range::Setup()
{
    // WARNING WARNING WARNING
    // Device pins connected to PinRange0Enable and PinRange1Enable
    // are not 5V tolerant. They are pulled up to 2.8V by the device
    // or pulled down to 0V by us. To work around this, when we want
    // to send a high signal, we set the pinMode to INPUT.
    // This puts the pin in high impedance mode and device pulls it to 2.8V
    //
    // Background:
    // This implementation uses a Polulu module, which does not perform
    // level shifting. While the module did not get fried with 5V,
    // communication over the I2C bus became impossible.
    // Adafruit module does have a level shifting diode, but it costs 150%
    // of the Polulu module. Therefore, for 2 modules, this hack saves $10.

    this->value0 = 0;
    this->initialized0 = false;
    this->value1 = 0;
    this->initialized1 = false;
    pinMode(PinI2CClock, OUTPUT);
    pinMode(PinI2CData, OUTPUT);
    // Program freezes if we initialize without the call to Wire.begin
    Wire.begin();

    // Reset the sensors
    pinMode(PinRange0Enable, OUTPUT);
    pinMode(PinRange1Enable, OUTPUT);
    digitalWrite(PinRange0Enable, 0);
    digitalWrite(PinRange1Enable, 0);
    delay(10);
    pinMode(PinRange0Enable, INPUT);
    pinMode(PinRange1Enable, INPUT);
    delay(10);
    pinMode(PinRange0Enable, OUTPUT);
    pinMode(PinRange1Enable, OUTPUT);
    digitalWrite(PinRange0Enable, 0);
    digitalWrite(PinRange1Enable, 0);
    delay(10);

    // Enable sensor 0 and set it up
    // WARNING: This pin is not 5V tolerant.
    // Set pin to input so that the device pulls its pin up to 2.8V
    pinMode(PinRange0Enable, INPUT);
    delay(10);
    // Device 0 should be now enabled. Change its address from default 0x29
    lox0.setAddress(0x30);
    if (lox0.init())
    {
        lox0.setTimeout(100);
        Serial.println("Setup complete: Range 0");
        this->initialized0 = true;
    }
    else
    {
        this->initialized0 = false;
        Serial.println("Error: Setup failed: Range 0");
    }

    // Enable sensor 1 and set it up
    // WARNING: This pin is not 5V tolerant.
    // Set pin to input so that the device pulls its pin up to 2.8V
    pinMode(PinRange1Enable, INPUT);
    delay(10);
    // Device 1 should be now enabled. Change its address from default 0x29
    lox1.setAddress(0x31);
    if (lox1.init())
    {
        lox1.setTimeout(100);
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
    Serial.printf("Information: Range0 at %x, Range1 at %x \n", a0, a1);
}

void Range::Input()
{
    if (this->initialized0)
    {
        this->value0 = lox0.readRangeSingleMillimeters();
        if (lox0.timeoutOccurred())
        {
            Serial.print("[R0 N/A].");
        }
        else
        {
            Serial.printf("[R0 % 3d]", this->value0);
        }
    }
    if (this->initialized1)
    {
        this->value1 = lox1.readRangeSingleMillimeters();
        if (lox1.timeoutOccurred())
        {
            Serial.print("[R1 N/A]");
        }
        else
        {
            Serial.printf("[R1 % 3d]", this->value1);
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
