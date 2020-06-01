#ifndef defaultHandler_h
#define defaultHandler_h

#include "../state.h"
#include "../handler.h"
class Composition;
class Debugger;
class Motor;
class ScoreSensor;
class Display;
class Digits;

class DefaultHandler: public Handler {
    Motor* motor;
    Debugger* debugger;
    ScoreSensor* scoreSensor;
    Display* display;
    Digits* digits;
    public:
        virtual void Setup(Composition* composition);
        virtual State SetState(State state, int turn);
        virtual void Act(State state, int turn);
};

#endif
