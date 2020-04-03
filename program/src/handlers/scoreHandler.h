#ifndef scoreHandler_h
#define scoreHandler_h

#include "../state.h"
#include "../Handler.h"
#include "../modules/motor.h"

class ScoreHandler: public Handler {
    public:
        virtual void setup();
        virtual void move(State state, Motor motor);
        virtual void debug(State state);
};

#endif
