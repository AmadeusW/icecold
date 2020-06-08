/* This example shows how to get single-shot range
 measurements from the VL53L0X. The sensor can optionally be
 configured with different ranging profiles, as described in
 the VL53L0X API user manual, to get better performance for
 a certain application. This code is based on the four
 "SingleRanging" examples in the VL53L0X API.

 The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X lox0;
VL53L0X lox1;

#define PinRange0Enable 16
#define PinRange1Enable 17

void setup()
{
    // Reset the sensors
    pinMode(PinRange0Enable, OUTPUT);
    pinMode(PinRange1Enable, OUTPUT);
    digitalWrite(PinRange0Enable, 0);
    digitalWrite(PinRange1Enable, 0);
    delay(10);

    Serial.begin(9600);
    delay(1000);
    Wire.begin();

    pinMode(PinRange1Enable, INPUT);
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
    }
    else
    {
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
        Serial.println("Setup complete: Range 1");
    }
    else
    {
        Serial.println("Error: Setup failed: Range 1");
    }

    uint8_t a0 = lox0.getAddress();
    uint8_t a1 = lox1.getAddress();
    Serial.printf("Information: Range0 at %x, Range1 at %x \n", a0, a1);
}

void loop()
{
    int value0 = lox0.readRangeSingleMillimeters();
    if (lox0.timeoutOccurred())
    {
        Serial.print("[R0 N/A].");
    }
    else
    {
        Serial.printf("[R0 % 4d]", value0);
    }

    int value1 = lox1.readRangeSingleMillimeters();
    if (lox1.timeoutOccurred())
    {
        Serial.print("[R1 N/A].");
    }
    else
    {
        Serial.printf("[R1 % 4d]", value1);
    }
    Serial.println();
    delay(500);
}
