// This file composes modules which run the program
// Each module must provide a method with
// bool parameter. True indicates execution of action, false indicates debug message
// int return.
#ifndef composition_h
#define composition_h

#include "state.h"
#include "handler.h"
class DefaultHandler;
class ScoreHandler;
class Debugger;
class Motor;
class BallSensor;
class Display;
class Digits;
class Range;
class Joystick;

class Composition {
        // Access handler by state
        Handler* handlers[MAX_State];
        // Access handler directly
        DefaultHandler* _defaultHandler;
        ScoreHandler* _scoreHandler;
        // Access module directly
        Debugger* _debugger;
        Motor* _motor;
        BallSensor* _ballSensor;
        Display* _display;
        Digits* _digits;
        Range* _range;
        Joystick* _joystick;
    public:
        void Compose();
        void Setup();
        void Input();
        void Output(int tick);
        Handler* GetHandler(State state);
        Debugger* GetDebugger();
        Motor* GetMotor();
        BallSensor* GetBallSensor();
        Display* GetDisplay();
        Digits* GetDigits();
        Range* GetRange();
        Joystick* GetJoystick();
};

#endif
