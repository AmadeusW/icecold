#include "Arduino.h"
#include "defaultHandler.h"
#include "../pins.h"
#include "../composition.h"
#include "../modules/debugger.h"
#include "../modules/display.h"
#include "../modules/motor.h"
#include "../modules/scoresensor.h"
#include "../modules/digits.h"
#include "../modules/range.h"

void DefaultHandler::Setup(Composition* composition)
{
    this->motor = composition->GetMotor();
    this->debugger = composition->GetDebugger();
    this->scoreSensor = composition->GetScoreSensor();
    this->display = composition->GetDisplay();
    this->digits = composition->GetDigits();
    this->range = composition->GetRange();

    Serial.println("Setup complete: DefaultHandler");
}

void DefaultHandler::Act(State state, int turn)
{
    switch (state) {
        case moveUp:
            this->motor->Move(true, 255);
            this->debugger->ShowCode(0x0b, turn);
            this->scoreSensor->SetTarget(false); // just for tests
            this->display->Write();
            this->digits->Write();
            return;
        case moveDown:
            this->motor->Move(false, 255);
            this->debugger->ShowCode(0x0d, turn);
            this->scoreSensor->SetTarget(true); // just for tests
            this->display->Write();
            this->digits->Write();
            return;
        case idle:
            this->motor->Brake();
            this->debugger->ShowCode(0x00, turn);
            this->display->Write();
            this->digits->Write();
            return;
        case errorInvalidInput:
            this->motor->Brake();
            this->debugger->ShowCode(0x33, turn);
            this->display->Write();
            this->digits->Write();
            return;
        default:
            return;
    }
}

State DefaultHandler::SetState(State state, int turn)
{
    // TODO: take ownership of joyAUp, etc.
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
        this->digits->SetValue(0);
        //Serial.printf("DefaultHandler sets INVALID state at turn %d \n", turn);
        return errorInvalidInput;
    }
    else if (joyAUp)
    {
        this->range->Read();
        int range = this->range->GetValue(0);
        this->digits->SetValue(range);
        Serial.printf("UP %d \n", range);
        return moveUp;
    }
    else if (joyADown)
    {
        this->range->Read();
        int range = this->range->GetValue(1);
        this->digits->SetValue(range);
        Serial.printf("DOWN %d \n", range);
        return moveDown;
    }
    else
    {
        this->digits->SetValue(turn);
        //Serial.printf("DefaultHandler sets IDLE state at turn %d \n", turn);
        return idle;
    }
}
