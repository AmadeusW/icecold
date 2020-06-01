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
class ScoreSensor;
class Display;
class Digits;

class Composition {
        // Access handler by state
        Handler* handlers[MAX_State];
        // Access handler directly
        DefaultHandler* _defaultHandler;
        ScoreHandler* _scoreHandler;
        // Access module directly
        Debugger* _debugger;
        Motor* _motor;
        ScoreSensor* _scoreSensor;
        Display* _display;
        Digits* _digits;
    public:
        void Compose();
        void Setup();
        void ReadPins();
        Handler* GetHandler(State state);
        Debugger* GetDebugger();
        Motor* GetMotor();
        ScoreSensor* GetScoreSensor();
        Display* GetDisplay();
        Digits* GetDigits();
};

#endif
