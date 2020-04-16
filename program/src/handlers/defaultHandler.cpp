#include "Arduino.h"
#include "defaultHandler.h"
#include "../pins.h"
#include "../composition.h"
#include "../modules/debugger.h"
#include "../modules/motor.h"
#include "../modules/scoresensor.h"

void DefaultHandler::Setup(Composition* composition)
{
    this->motor = composition->GetMotor();
    this->debugger = composition->GetDebugger();
    this->scoreSensor = composition->GetScoreSensor();
}

void DefaultHandler::Act(State state, int turn)
{
    switch (state) {
        case moveUp:
            this->motor->Move(true, 255);
            this->debugger->ShowCode(0x0b, turn);
            this->scoreSensor->SetTarget(false); // just for tests
            return;
        case moveDown:
            this->motor->Move(false, 255);
            this->debugger->ShowCode(0x0d, turn);
            this->scoreSensor->SetTarget(true); // just for tests
            return;
        case idle:
            this->motor->Brake();
            this->debugger->ShowCode(0x00, turn);
            return;
        case errorInvalidInput:
            this->motor->Brake();
            this->debugger->ShowCode(0x33, turn);
            return;
        default:
            return;
    }
}

State DefaultHandler::SetState(State state, int turn)
{
    if (this->scoreSensor->IsLosing())
    {
        return lost;
    }
    if (this->scoreSensor->IsScoring())
    {
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
