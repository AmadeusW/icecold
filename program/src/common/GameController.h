#ifndef GameController_h
#define GameController_h

#include "GameState.h"

class GameController {
    public:
        GameController();
        void setup(GameState& state);
        void updateState(GameState& state);
};

#endif