#include "Arduino.h"
#include "../lib/Servo/Servo.h"
#include "scoreHandler.h"
#include "../modules/motor.h"
#include "../modules/debugger.h"
#include "../composition.h"
#include "../Handler.h"
#include "../pins.h"

void ScoreHandler::Setup(Composition* composition)
{
    this->ballServo.attach(PinServo);
    this->_motor = composition->GetMotor();
    this->_debugger = composition->GetDebugger();
}

void ScoreHandler::Act(State state, int turn)
{
    switch (state) {
        case scored:
            this->_debugger->ShowCode(0xf4, turn);
            //this->ballServo.write((unfreezeTurn - turn) * 8);
            return;
        case lost: // just for testing
            this->_debugger->ShowCode(0xfe, turn);
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
