#ifndef SIMULATOR_MODULE_H
#define SIMULATOR_MODULE_H

#include "../common/module.h"
#include <cstring>

class SimulatorModule : public Module {
private:
    std::string serializeGameState(GameState& state);
public:
    void setup(GameState& state);
    void getInput(GameState& state);
    void setOutput(GameState& state);
};

#endif