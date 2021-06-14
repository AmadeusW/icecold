#ifndef debugger_h
#define debugger_h

#include "../module.h"

class Debugger : public OutputModule {
    int code;
    public:
        virtual void Setup();
        virtual void Output(int tick);
        void SetCode(int code);
};

#endif