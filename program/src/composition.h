// This file composes modules which run the program
// Each module must provide a method with
// bool parameter. True indicates execution of action, false indicates debug message
// int return.
#ifndef composition_h
#define composition_h

#include "state.h"

int (*modules[MAX_State]) (bool);
int compose();

enum Methods {
   METHOD_SETUP,
   METHOD_WORK,
   METHOD_DEBUG,
   MAX_Methods
};

#endif
