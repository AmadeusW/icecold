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
    this->SetScore(0);
}

void Display::Read()
{
    // This module does not read any pins
}

void Display::SetScore(int score)
{
    this->score = score;
}

void Display::Write()
{
    byte dataArray[6];
    dataArray[0] = 0x80; // 1000'0000
    dataArray[1] = 0xC0; // 1100'0000
    dataArray[2] = 0xE0; // 1110'0000
    dataArray[3] = 0xF0; // 1111'0000
    dataArray[4] = 0xF8; // 1111'1000
    dataArray[5] = 0xFC; // 1111'1100

    digitalWrite(PinSerialLatch, 0); // Clear
    shiftOut(PinSerialData, PinSerialClock, LSBFIRST, dataArray[this->score]);
    digitalWrite(PinSerialLatch, 1); // Latch
}
