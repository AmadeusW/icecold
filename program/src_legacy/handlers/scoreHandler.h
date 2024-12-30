#ifndef scoreHandler_h
#define scoreHandler_h

#include "../lib/Servo/Servo.h"
#include "../state.h"
#include "../handler.h"
class Composition;
class Motor;
class Servo;
class Debugger;
class Display;
class Digits;

class ScoreHandler: public Handler {
    Servo ballServo; // TODO: get it from the composition
    Motor* _motor;
    Debugger* _debugger;
    Display* _display;
    Digits* _digits;
    int _enteredTurn = -1;
    State _enteredState = idle;
    int health = 10;
    int level = 1;
    void IncreaseLevel();
    void DecreaseHealth();
    public:
        virtual void Setup(Composition* composition);
        virtual State SetState(State state, int turn);
        virtual void Act(State state, int turn);
};

#endif
