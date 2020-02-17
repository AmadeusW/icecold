#ifndef state_h
#define state_h

#include "Arduino.h"

// This file declares all possible states
// and variables which store the state

enum State {
   uninitialized = 0,
   idle,
   moveUp,
   moveDown,
   errorInvalidInput,
   scored, // TODO: add multiple stages for scored
   MAX_State
};

extern State state;
extern int turn;

extern bool freezeState;
extern int unfreezeTurn;

#endif
