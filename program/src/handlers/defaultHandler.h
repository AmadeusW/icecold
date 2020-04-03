#ifndef defaultHandler_h
#define defaultHandler_h

#include "../state.h"
#include "../Handler.h"

class DefaultHandler: public Handler {
    public:
        virtual void setup();
        virtual void work(State state);
        virtual void debug(State state);
};

#endif
