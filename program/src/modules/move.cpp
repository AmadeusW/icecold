#include "Arduino.h"
#include "move.h"
#include "../pins.h"

void MoveModule::setup()
{
    startMotor();
}

void MoveModule::work(State state)
{
    switch (state) {
        case moveUp:
            move(true, 255);
            return;
        case moveDown:
            move(false, 255);
            return;
        case idle:
        case errorInvalidInput:
            brake();
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
