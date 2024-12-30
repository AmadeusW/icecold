#ifndef defaultHandler_h
#define defaultHandler_h

#include "../state.h"
#include "../handler.h"
class Composition;
class Debugger;
class Motor;
class BallSensor;
class Display;
class Digits;
class Range;
class Joystick;

class DefaultHandler: public Handler {
    Motor* motor;
    Debugger* debugger;
    BallSensor* ballSensor;
    Display* display;
    Digits* digits;
    Range* range;
    Joystick* joystick;
    public:
        virtual void Setup(Composition* composition);
        virtual State SetState(State state, int turn);
        virtual void Act(State state, int turn);
};

#endif
