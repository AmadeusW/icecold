#include "Arduino.h"
#include "../lib/Servo/Servo.h"
#include "scoreHandler.h"
#include "../modules/motor.h"
#include "../modules/debugger.h"
#include "../modules/display.h"
#include "../modules/digits.h"
#include "../composition.h"
#include "../Handler.h"
#include "../pins.h"

void ScoreHandler::Setup(Composition* composition)
{
    //this->ballServo.attach(PinServo); TODO: set it up
    this->_motor = composition->GetMotor();
    this->_debugger = composition->GetDebugger();
    this->_display = composition->GetDisplay();
    this->_digits = composition->GetDigits();

    this->health = 10;
    this->level = 1;

    this->_display->SetHealth(this->health);
    this->_display->SetLevel(this->level);
    this->_digits->SetValue(0);
}

void ScoreHandler::Act(State state, int turn)
{
    switch (state) {
        case scored:
            this->_debugger->ShowCode(0xf4, turn);
            this->_display->Write();
            this->_digits->Write();
            //this->ballServo.write((unfreezeTurn - turn) * 8);
            return;
        case lost: // just for testing
            this->_debugger->ShowCode(0xfe, turn);
            this->_display->Write();
            this->_digits->Write();
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
            IncreaseLevel();
        }
        else if (state == lost)
        {
            DecreaseHealth();
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

void ScoreHandler::IncreaseLevel()
{
    this->level++;
    // Note: temporarily, reset level to 1.
    // In the future, we will enter a victory stage and then reset game back to level 1
    if (this->level > 10)
    {
        this->level = 1;
    }
    this->_display->SetLevel(this->level);
    this->_digits->SetValue(this->level);
}

void ScoreHandler::DecreaseHealth()
{
    this->health--;
    if (this->health < 0)
    {
        this->health = 10;
    }
    this->_display->SetHealth(this->health);
    this->_digits->SetValue(this->health);
}
