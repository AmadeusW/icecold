// Entry point for the code running in the simulator

#include "../composition.h"
#include "../GameController.h"
#include "../GameEngine.h"
#include "../GameState.h"

#include "../module.h"
#include "simulatorModule.h"

GameEngine* engine;

void setup() {
    // Example usage
    SimulatorModule simulatorModule{};
    Module* modules[] = {&simulatorModule};
    Composition composition(modules, 1);
    GameController controller;
    GameState state;
    engine = new GameEngine(composition, controller, state);
    engine->setup();
}

void loop() {
    engine->loop();
}
