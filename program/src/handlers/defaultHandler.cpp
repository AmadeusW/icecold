#include "Arduino.h"
#include "defaultHandler.h"
#include "../pins.h"
#include "../composition.h"
#include "../modules/debugger.h"
#include "../modules/motor.h"

void DefaultHandler::Setup(Composition* composition)
{
    this->motor = composition->GetMotor();
    this->debugger = composition->GetDebugger();
}

void DefaultHandler::Act(State state, int turn)
{
    switch (state) {
        case moveUp:
            this->motor->move(true, 255);
            this->debugger->ShowCode(0x0b, turn);
            return;
        case moveDown:
            this->motor->move(false, 255);
            this->debugger->ShowCode(0x0d, turn);
            return;
        case idle:
        case errorInvalidInput:
            this->motor->brake();
            this->debugger->ShowCode(0x33, turn);
            return;
        default:
            return;
    }
}

State DefaultHandler::SetState(State state, int turn)
{
    if (isScoring)
    {
        return scored;
    }
    else if (joyAUp && joyADown)
    {
        return errorInvalidInput;
    }
    else if (joyAUp)
    {
        return moveUp;
    }
    else if (joyADown) // TODO: add another angle limiter
    {
        return moveDown;
    }
    else
    {
        return idle;
    }
}
