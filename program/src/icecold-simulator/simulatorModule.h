#ifndef MOCKED_MODULE_H
#define MOCKED_MODULE_H

#include "../common/module.h"
#include "../common/GameState.h"

class SimulatorModule : public Module {
public:
    void setup(GameState& state) override { /* Do nothing */ }
    void getInput(GameState& state) override { /* Do nothing */ }
    void setOutput(GameState& state) override { 
        // Record the state for testing
        lastState = state;
    }
    
    GameState lastState;  // For verification in tests
};

#endif
