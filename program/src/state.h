#ifndef state_h
#define state_h

// This file declares all possible states
// and variables which store the state

enum State {
   uninitialized = 0,
   idle,
   moveUp,
   moveDown,
   errorInvalidInput,
   scored,
   lost,
   MAX_State
};

extern State state;
extern int turn;

#endif
