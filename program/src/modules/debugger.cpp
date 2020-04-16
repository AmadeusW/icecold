#include "Arduino.h"
#include "debugger.h"
#include "../module.h"

#define LED 13

void Debugger::Setup() {
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
}

void Debugger::Read() {
    // This module does not read any pins
}

void Debugger::ShowCode(int code, int turn)
{
    // Length in bits of supported codes
    int codeLength = 8;

    // Index of turn in the sequence of length codeLength
    int i = turn % codeLength;
    
    // Whether LED should be lit during the ith element of the sequence
    int lit = (code >> i) & 1;
    
    digitalWrite(LED, lit);
}