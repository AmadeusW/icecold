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
            this->motor->brake();
            this->debugger->ShowCode(0x00, turn);
            return;
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
        //Serial.printf("DefaultHandler sets SCORED state at turn %d \n", turn);
        return scored;
    }
    else if (joyAUp && joyADown)
    {
        //Serial.printf("DefaultHandler sets INVALID state at turn %d \n", turn);
        return errorInvalidInput;
    }
    else if (joyAUp)
    {
        //Serial.printf("DefaultHandler sets UP state at turn %d \n", turn);
        return moveUp;
    }
    else if (joyADown) // TODO: add another angle limiter
    {
        //Serial.printf("DefaultHandler sets DOWN state at turn %d \n", turn);
        return moveDown;
    }
    else
    {
        //Serial.printf("DefaultHandler sets IDLE state at turn %d \n", turn);
        return idle;
    }
}
