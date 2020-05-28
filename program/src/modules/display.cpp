#include "Arduino.h"
#include "display.h"
#include "../pins.h"

void Display::Setup()
{
    pinMode(PinSerialClock, OUTPUT);
    pinMode(PinSerialLatch, OUTPUT);
    pinMode(PinSerialData, OUTPUT);
    this->Test();
    this->Write();
}

void Display::Read()
{
    // This module does not read any pins
}

void Display::SetLevel(int level)
{
    this->level = level;
}

void Display::SetHealth(int health)
{
    this->health = health;
}

void Display::Test()
{
    long testArray[10];
    testArray[0] = 0x001;
    testArray[1] = 0x002;
    testArray[2] = 0x004;
    testArray[3] = 0x008;
    testArray[4] = 0x018;
    testArray[5] = 0x038;
    testArray[6] = 0x030;
    testArray[7] = 0x020;
    testArray[8] = 0x040;
    testArray[9] = 0x080;
    for (int i = 0; i < 10; i++)
    {
        long testCode = testArray[i];
        byte transmission1 = testCode & 0xFF;
        byte transmission2 = testCode & 0xFF;
        byte transmission3 = testCode & 0xFF;
        byte transmission4 = testCode & 0xFF;

        digitalWrite(PinSerialLatch, 0); // Clear
        shiftOut(PinSerialData, PinSerialClock, LSBFIRST, transmission1);
        shiftOut(PinSerialData, PinSerialClock, LSBFIRST, transmission2);
        shiftOut(PinSerialData, PinSerialClock, LSBFIRST, transmission3);
        shiftOut(PinSerialData, PinSerialClock, LSBFIRST, transmission4);
        digitalWrite(PinSerialLatch, 1); // Latch
        delay(100);
    }
}

void Display::Write()
{
    long levelArray[11];
    levelArray[0] = 0x000; // 0000
    levelArray[1] = 0x001; // 0001
    levelArray[2] = 0x003; // 0011
    levelArray[3] = 0x007; // 0111
    levelArray[4] = 0x00F; // 1111
    levelArray[5] = 0x01F;
    levelArray[6] = 0x03F;
    levelArray[7] = 0x07F;
    levelArray[8] = 0x0FF;
    levelArray[9] = 0x1FF;
    levelArray[10] = 0x3FF;

    long healthArray[11];
    healthArray[0] = 0x000; // 0000
    healthArray[1] = 0x001; // 0001
    healthArray[2] = 0x003; // 0011
    healthArray[3] = 0x007; // 0111
    healthArray[4] = 0x00F; // 1111
    healthArray[5] = 0x01F;
    healthArray[6] = 0x03F;
    healthArray[7] = 0x07F;
    healthArray[8] = 0x0FF;
    healthArray[9] = 0x1FF;
    healthArray[10] = 0x3FF;

    long targetArray[11];
    targetArray[0] = 0x000; // 0000
    targetArray[1] = 0x001; // 0001
    targetArray[2] = 0x002; // 0010
    targetArray[3] = 0x004; // 0100
    targetArray[4] = 0x008; // 1000
    targetArray[5] = 0x010;
    targetArray[6] = 0x020;
    targetArray[7] = 0x040;
    targetArray[8] = 0x080;
    targetArray[9] = 0x100;
    targetArray[10] = 0x200;

    long healthCode = healthArray[this->health];
    long levelCode = levelArray[this->level];
    long targetCode = targetArray[this->level];

    // We are stuffing 3x10 bits of information into 4 bytes
    //  Input: 01 | 012345 6789 | 0123 456789 | 01 23456789
    // Output: 01   234567 0123   4567 012345   67 01234567
    //        |-2-------6-|-4-------4-|-6-------2-|-8------|

    byte transmission1 = healthCode & 0xFF;
    byte transmission2 = ((healthCode >> 8) & 0x03) | ((levelCode << 2) & 0xFC);
    byte transmission3 = ((levelCode >> 6) & 0x0F) | ((targetCode << 4) & 0xF0);
    byte transmission4 = 0 | ((targetCode << 6) & 0x3F);

    digitalWrite(PinSerialLatch, 0); // Clear
    shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission1);
    shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission2);
    shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission3);
    shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission4);
    digitalWrite(PinSerialLatch, 1); // Latch

    Serial.print(" serial:");
    Serial.print(transmission1);
    Serial.print(" ");
    Serial.print(transmission2);
    Serial.print(" ");
    Serial.print(transmission3);
    Serial.print(" ");
    Serial.print(transmission4);
    Serial.println(".");
}
