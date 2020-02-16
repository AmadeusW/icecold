// This file composes modules which run the program
// Each module must provide a method with
// bool parameter. True indicates execution of action, false indicates debug message
// int return.
#ifndef composition_h
#define composition_h

#include "state.h"

class GameModule {
   public:
      virtual void setup() = 0;
      virtual void work(State state) = 0;
      virtual void debug(State state) = 0;
};

GameModule** modules = new GameModule*[MAX_State];
void compose();

#endif
