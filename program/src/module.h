// This file composes modules which run the program
// Each module must provide a method with
// bool parameter. True indicates execution of action, false indicates debug message
// int return.
#ifndef module_h
#define module_h

#include "state.h"

class Module {
   public:
      virtual void setup() = 0;
      virtual void work(State state) = 0;
      virtual void debug(State state) = 0;
};

#endif
