#ifndef debugger_h
#define debugger_h

class Debugger /* add base class public Module */ {
    public:
        virtual void setup();
        virtual void ShowCode(int code, int turn);
};

#endif