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
            this->_debugger->ShowCode(0xa8, turn);
            //this->ballServo.write((unfreezeTurn - turn) * 8);
            return;
        case moveDown: // just for testing
            this->_debugger->ShowCode(0xab, turn);
            this->_motor->move(false, 255);
            return;
        default:
            this->_motor->brake();
    }
}

State ScoreHandler::SetState(State state, int turn)
{
    if (this->_enteredState == -1)
    {
        //Serial.printf("ScoreHandler initializes SCORED state at turn %d \n", turn);
        this->_enteredState = turn;
    }

    if (this->_enteredState + 50 < turn)
    {
        //Serial.printf("ScoreHandler enters IDLE state at turn %d \n", turn);
        this->_enteredState = -1;
        return idle;
    }
    else
    {
        //Serial.printf("ScoreHandler sets SCORED state at turn %d \n", turn);
        return scored;
    }
}
