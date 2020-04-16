#ifndef debugger_h
#define debugger_h

#include "../module.h"

class Debugger : public Module {
    public:
        virtual void Setup();
        virtual void Read();
        void ShowCode(int code, int turn);
};

#endif