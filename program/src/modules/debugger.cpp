#include "Arduino.h"
#include "debugger.h"
#include "../pins.h"

void Debugger::setup() {
    digitalWrite(LED, LOW);
}

void Debugger::ShowCode(int code, int turn)
{
    // Length in bits of supported codes
    int codeLength = 8;

    // Index of turn in the sequence of length codeLength
    int i = turn % codeLength;
    
    // Whether LED should be lit during the sequence i 
    int lit = (codeLength >> i) & 1;
    
    digitalWrite(LED, lit);
}