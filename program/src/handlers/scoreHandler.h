#ifndef scoreHandler_h
#define scoreHandler_h

#include "../state.h"
#include "../Handler.h"

class ScoreHandler: public Handler {
    public:
        virtual void setup();
        virtual void work(State state);
        virtual void debug(State state);
};

#endif
