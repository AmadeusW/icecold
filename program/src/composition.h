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

class Composition {
        Handler* handlers[MAX_State];
        Debugger* _debugger;
        Motor* _motor;
        DefaultHandler* _defaultHandler;
        ScoreHandler* _scoreHandler;
    public:
        void Compose();
        void Setup();
        Handler* GetHandler(State state);
        Debugger* GetDebugger();
        Motor* GetMotor();
};

#endif
