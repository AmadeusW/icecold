// This file defines a module responsible for reading from and writing to pins
#ifndef module_h
#define module_h

#include "state.h"

class Module {
   public:
      virtual void Setup() = 0;
};

class InputModule : public Module {
   public:
      virtual void Input() = 0;
};

class OutputModule : public Module {
   public:
      virtual void Output(int tick) = 0;
};

#endif
