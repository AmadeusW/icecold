// This file defines a module responsible for reading from and writing to pins
#ifndef module_h
#define module_h

#include "state.h"

class Module {
   public:
      virtual void Setup() = 0;
      virtual void Read() = 0;
};

#endif
