#ifndef MOCKED_MODULE_H
#define MOCKED_MODULE_H

#include "../module.h"
#include "../GameState.h"

class MockedModule : public Module {
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
