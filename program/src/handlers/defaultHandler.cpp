#include "Arduino.h"
#include "defaultHandler.h"
#include "../pins.h"
#include "../modules/motor.h"

void DefaultHandler::setup()
{
}

void DefaultHandler::move(State state, Motor motor)
{
    switch (state) {
        case moveUp:
            motor.move(true, 255);
            return;
        case moveDown:
            motor.move(false, 255);
            return;
        case idle:
        case errorInvalidInput:
            motor.brake();
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
