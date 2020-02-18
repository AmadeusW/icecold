#ifndef movemodule_h
#define movemodule_h

#include "../state.h"
#include "../module.h"

class MoveModule: public Module {
    public:
        virtual void setup();
        virtual void work(State state);
        virtual void debug(State state);
};

#endif
