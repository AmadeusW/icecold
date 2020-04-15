// This file defines a handler responsible for running the program at a given game state
#ifndef handler_h
#define handler_h

#include "state.h"
class Composition;

class Handler {
   public:
      virtual void Setup(Composition* composition) = 0;
      virtual State SetState(State state, int turn) = 0;
      virtual void Act(State state, int turn) = 0;
};

#endif
