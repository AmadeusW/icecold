#ifndef scoremodule_h
#define scoremodule_h

#include "../state.h"
#include "../composition.h"

class ScoreModule: public GameModule {
    public:
        virtual void setup();
        virtual void work(State state);
        virtual void debug(State state);
};

#endif
