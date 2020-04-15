#include "Arduino.h"
#include "composition.h"
#include "handlers/defaultHandler.h"
#include "handlers/scoreHandler.h"
#include "modules/debugger.h"
#include "modules/motor.h"

void Composition::Compose()
{
    this->_defaultHandler = new DefaultHandler();
    this->_scoreHandler = new ScoreHandler();
    this->_debugger = new Debugger();
    this->_motor = new Motor();

    this->handlers[idle] = _defaultHandler;
    this->handlers[moveUp] = _defaultHandler;
    this->handlers[moveDown] = _defaultHandler;
    this->handlers[scored] = _scoreHandler;
    this->handlers[errorInvalidInput] = _defaultHandler;
}

void Composition::Setup()
{
    this->_motor->setup();
    this->_debugger->setup();
    for (int stateId = 0; stateId < (int)MAX_State; stateId++)
    {
        Handler* handler = GetHandler((State)stateId);
        if (handler == 0)
        {
            Serial.print("No setup for ");
            Serial.print(stateId);
            Serial.println(".");
        }
        else
        {
            Serial.print("Setting up handler ");
            Serial.print(stateId);
            Serial.println("...");
            handler->Setup(this);
        }
    }
}

Handler* Composition::GetHandler(State state)
{
    return this->handlers[state];
}

Motor* Composition::GetMotor()
{
    return this->_motor;
}

Debugger* Composition::GetDebugger()
{
    return this->_debugger;
}
