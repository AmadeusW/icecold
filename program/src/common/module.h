#ifndef MODULE_H
#define MODULE_H

#include "GameState.h"

class Module {
public:
    virtual ~Module() = default;
    virtual void setup(GameState& state) = 0;
    virtual void getInput(GameState& state) = 0;
    virtual void setOutput(GameState& state) = 0;
};

#endif