// This file composes modules which run the program
// Each module must provide a method with
// bool parameter. True indicates execution of action, false indicates debug message
// int return.
#ifndef composition_h
#define composition_h

#include "state.h"
#include "Handler.h"

class Composition {
    public:
        Handler* getHandler(State state);
        void compose();
};

#endif
