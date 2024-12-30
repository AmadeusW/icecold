#ifndef state_h
#define state_h

// This file declares all possible states
// and variables which store the state

enum State {
   uninitialized = 0,
   newGame, // game is about to start
   shooter, // ball is in the shooter lane and will be deployed
   playfield, // ball is in the playfield and is player-controlled
   outlane, // ball is in the out lane, either through correct or incorrect target
   gameOverWon, // player scored all targets
   gameOverLost, // player lost all lifes
   MAX_State
};

#endif
