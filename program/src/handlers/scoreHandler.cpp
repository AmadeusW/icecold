#include "Arduino.h"
#include "../lib/Servo/Servo.h"
#include "scoreHandler.h"
#include "../modules/motor.h"
#include "../modules/debugger.h"
#include "../modules/display.h"
#include "../composition.h"
#include "../Handler.h"
#include "../pins.h"

void ScoreHandler::Setup(Composition* composition)
{
    this->ballServo.attach(PinServo);
    this->_motor = composition->GetMotor();
    this->_debugger = composition->GetDebugger();
    this->_display = composition->GetDisplay();
}

void ScoreHandler::Act(State state, int turn)
{
    switch (state) {
        case scored:
            this->_debugger->ShowCode(0xf4, turn);
            this->_display->Write();
            //this->ballServo.write((unfreezeTurn - turn) * 8);
            return;
        case lost: // just for testing
            this->_debugger->ShowCode(0xfe, turn);
            this->_display->Write();
            return;
        default:
            return;
    }
}

State ScoreHandler::SetState(State state, int turn)
{
    if (this->_enteredTurn == -1)
    {
        //Serial.printf("ScoreHandler initializes SCORED state at turn %d \n", turn);
        this->_enteredTurn = turn;
        this->_enteredState = state;
        if (state == scored)
        {
            IncreaseScore();
        }
        else if (state == lost)
        {
            DecreaseLife();
        }
    }

    if (this->_enteredTurn + 50 < turn)
    {
        //Serial.printf("ScoreHandler enters IDLE state at turn %d \n", turn);
        this->_enteredTurn = -1;
        return idle;
    }
    else
    {
        //Serial.printf("ScoreHandler sets SCORED state at turn %d \n", turn);
        return this->_enteredState;
    }
}

void ScoreHandler::IncreaseScore()
{
    this->_score++;
    if (this->_score > 5)
    {
        this->_score = 0;
    }
    this->_display->SetScore(this->_score);
}

void ScoreHandler::DecreaseLife()
{
    this->_score--;
    if (this->_score < 0)
    {
        this->_score = 5;
    }
    this->_display->SetScore(this->_score);
}
