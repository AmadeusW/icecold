#ifndef movemodule_h
#define movemodule_h

#include "../state.h"
#include "../composition.h"

class MoveModule: public GameModule {
    public:
        virtual void setup();
        virtual void work(State state);
        virtual void debug(State state);
};

#endif
