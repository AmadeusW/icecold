#include "Arduino.h"
#include "composition.h"
#include "handlers/defaultHandler.h"
#include "handlers/scoreHandler.h"
#include "modules/debugger.h"
#include "modules/motor.h"
#include "modules/scoresensor.h"

void Composition::Compose()
{
    // Create modules
    this->_debugger = new Debugger();
    this->_motor = new Motor();
    this->_scoreSensor = new ScoreSensor();

    // Create handlers
    this->_defaultHandler = new DefaultHandler();
    this->_scoreHandler = new ScoreHandler();

    // Associate handlers with states
    this->handlers[idle] = _defaultHandler;
    this->handlers[moveUp] = _defaultHandler;
    this->handlers[moveDown] = _defaultHandler;
    this->handlers[scored] = _scoreHandler;
    this->handlers[lost] = _scoreHandler;
    this->handlers[errorInvalidInput] = _defaultHandler;
}

void Composition::Setup()
{
    // Setup modules
    this->_motor->Setup();
    this->_debugger->Setup();
    this->_scoreSensor->Setup();

    // Setup handlers
    this->_defaultHandler->Setup(this);
    this->_scoreHandler->Setup(this);
}

void Composition::ReadPins()
{
    this->_motor->Read();
    this->_debugger->Read();
    this->_scoreSensor->Read();
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

ScoreSensor* Composition::GetScoreSensor()
{
    return this->_scoreSensor;
}
