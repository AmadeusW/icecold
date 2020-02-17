#ifndef scoremodule_h
#define scoremodule_h

#include "../state.h"
#include "../module.h"

class ScoreModule: public Module {
    public:
        virtual void setup();
        virtual void work(State state);
        virtual void debug(State state);
};

#endif
