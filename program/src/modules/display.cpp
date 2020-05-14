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
    this->TestSequence();
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

void Display::TestSequence()
{
    for (int i = 0; i < 8; i++)
    {
        byte code = 1 << i;
        digitalWrite(PinSerialLatch, 0); // Clear
        shiftOut(PinSerialData, PinSerialClock, LSBFIRST, code);
        shiftOut(PinSerialData, PinSerialClock, LSBFIRST, code);
        shiftOut(PinSerialData, PinSerialClock, LSBFIRST, code);
        digitalWrite(PinSerialLatch, 1); // Latch
        delay(50);
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
    byte transmission1 = healthCode >> 8 & 0x03;
    byte transmission2 = (healthCode >> 8 & 0x03) | (levelCode << 2 & 0xFC);
    byte transmission3 = levelCode & 0xFF;

    digitalWrite(PinSerialLatch, 0); // Clear
    shiftOut(PinSerialData, PinSerialClock, LSBFIRST, transmission3);
    shiftOut(PinSerialData, PinSerialClock, LSBFIRST, transmission2);
    shiftOut(PinSerialData, PinSerialClock, LSBFIRST, transmission1);
    digitalWrite(PinSerialLatch, 1); // Latch
}
