// This file defines a handler responsible for running the program at a given game state
#ifndef handler_h
#define handler_h

#include "state.h"

class Handler {
   public:
      virtual void setup() = 0;
      virtual void work(State state) = 0;
      // virtual void move(State state, Motor motor) = 0;
      virtual void debug(State state) = 0;
      // virtual void display(State state, Display display) = 0;
      // virtual void debug(State state, DebugLed led) = 0;
};

#endif
