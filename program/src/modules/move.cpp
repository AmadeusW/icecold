#include "Arduino.h"
#include "move.h"
#include "../pins.h"
#include "../motor.h"

void MoveModule::setup()
{
    motorSetup();
}

void MoveModule::work(State state)
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

void MoveModule::debug(State state)
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
