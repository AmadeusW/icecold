#include "Arduino.h"
#include "defaultHandler.h"
#include "../pins.h"
#include "../motor.h"

void DefaultHandler::setup()
{
    motorSetup();
}

void DefaultHandler::work(State state)
{
    switch (state) {
        case moveUp:
            motorMove(true, 255);
            return;
        case moveDown:
            motorMove(false, 255);
            return;
        case idle:
        case errorInvalidInput:
            ::motorBrake();
            return;
        default:
            return;
    }
}

void DefaultHandler::debug(State state)
{
    switch (state) {
        case moveUp:
        case moveDown:
            digitalWrite(LED, HIGH);
            return;
        case errorInvalidInput:
            digitalWrite(LED, turn % 2 == 0 ? HIGH : LOW);
            return;
        default:
            return;
    }
}
