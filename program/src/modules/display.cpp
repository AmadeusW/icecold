#include "Arduino.h"
#include "display.h"
#include "../pins.h"

#define PinSerialClock 8
#define PinSerialLatch 9
#define PinSerialData 12

void Display::Setup()
{
    pinMode(PinSerialClock, OUTPUT);
    pinMode(PinSerialLatch, OUTPUT);
    pinMode(PinSerialData, OUTPUT);
    this->Test();
    this->SetLevel(0);
    this->SetHealth(0);
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
    long testArray[11];
    testArray[0] = 0x000; // 0000
    testArray[1] = 0x001; // 0001
    testArray[2] = 0x003; // 0011
    testArray[3] = 0x007; // 0111
    testArray[4] = 0x00F; // 1111
    testArray[5] = 0x01F;
    testArray[6] = 0x03F;
    testArray[7] = 0x07F;
    testArray[8] = 0x0FF;
    testArray[9] = 0x1FF;
    testArray[10] = 0x3FF;
    for (int i = 0; i < 11; i++)
    {
        long testCode = testArray[i];
        byte transmission1 = testCode & 0xFF;
        byte transmission2 = ((testCode & 0x300) >> 8) | ((testCode << 2) & 0xFC);

        digitalWrite(PinSerialLatch, 0); // Clear
        shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission2);
        shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission1);
        digitalWrite(PinSerialLatch, 1); // Latch
        delay(30);
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

    long levelCode = levelArray[this->level];
    long healthCode = healthArray[this->health];
    // long targetCode = targetArray[this->level];
    byte transmission1 = levelCode & 0xFF;
    byte transmission2 = ((levelCode & 0x0300) >> 8) | (healthCode << 2 & 0xFC);
    byte transmission3 = healthCode & 0xFF;

    digitalWrite(PinSerialLatch, 0); // Clear
    shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission3);
    shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission2);
    shiftOut(PinSerialData, PinSerialClock, MSBFIRST, transmission1);
    digitalWrite(PinSerialLatch, 1); // Latch
}
