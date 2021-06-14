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
            this->motor->MoveLeft(true, 255);
            this->motor->MoveRight(true, 255);
            this->debugger->SetCode(0x0b);
            this->display->Output(turn);
            this->digits->Output(turn);
            return;
        case moveDown:
            this->motor->MoveLeft(false, 255);
            this->motor->MoveRight(false, 255);
            this->debugger->SetCode(0x0d);
            this->display->Output(turn);
            this->digits->Output(turn);
            return;
        case idle:
            this->motor->Brake();
            this->debugger->SetCode(0x00);
            this->display->Output(turn);
            this->digits->Output(turn);
            return;
        case errorInvalidInput:
            this->motor->Brake();
            this->debugger->SetCode(0x33);
            this->display->Output(turn);
            this->digits->Output(turn);
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
        this->range->Input();
        int range = this->range->GetValue(0);
        this->digits->SetValue(range);
        Serial.printf("UP %d \n", range);
        return moveUp;
    }
    else if (joyADown)
    {
        this->range->Input();
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
