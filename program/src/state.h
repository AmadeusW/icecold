#ifndef state_h
#define state_h

#include "Arduino.h"

// This file declares all possible states
// and variables which store the state

enum States {
   uninitialized = 0,
   idle,
   moveUp,
   moveDown,
   errorInvalidInput,
   scored, // TODO: add multiple stages for scored
   MAX_State
};

static int state = 0;
static int turn = 0;

static bool freezeState = false;
static int unfreezeTurn = 0;

#endif
