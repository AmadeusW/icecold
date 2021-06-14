#include "Arduino.h"
#include "composition.h"
#include "handlers/defaultHandler.h"
#include "handlers/scoreHandler.h"
#include "modules/debugger.h"
#include "modules/display.h"
#include "modules/motor.h"
#include "modules/scoresensor.h"
#include "modules/digits.h"
#include "modules/range.h"

void Composition::Compose()
{
    // Create modules
    this->_debugger = new Debugger();
    this->_motor = new Motor();
    this->_scoreSensor = new ScoreSensor();
    this->_display = new Display();
    this->_digits = new Digits();
    this->_range = new Range();

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
    this->_debugger->Setup();
    this->_display->Setup();
    this->_motor->Setup();
    this->_scoreSensor->Setup();
    this->_digits->Setup();
    this->_range->Setup();

    // Setup handlers
    this->_defaultHandler->Setup(this);
    this->_scoreHandler->Setup(this);
}

void Composition::Input()
{
    this->_scoreSensor->Input();
    this->_range->Input();
}

void Composition::Output(int tick)
{
    this->_debugger->Output(tick);
    this->_display->Output(tick);
    this->_motor->Output(tick);
    this->_digits->Output(tick);
}

Handler* Composition::GetHandler(State state)
{
    return this->handlers[state];
}

Debugger* Composition::GetDebugger()
{
    return this->_debugger;
}

Display* Composition::GetDisplay()
{
    return this->_display;
}

Motor* Composition::GetMotor()
{
    return this->_motor;
}

ScoreSensor* Composition::GetScoreSensor()
{
    return this->_scoreSensor;
}

Digits* Composition::GetDigits()
{
    return this->_digits;
}

Range* Composition::GetRange()
{
    return this->_range;
}
