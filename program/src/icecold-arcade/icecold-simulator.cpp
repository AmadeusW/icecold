// Entry point for the code running in the simulator

#include "composition.h"
#include "GameController.h"
#include "GameEngine.h"
#include "GameState.h"

#include "module.h"
#include "modules/MockedModule.h"

GameEngine* engine;

void setup() {
    // Example usage
    MockedModule mockedModule{};
    Module* modules[] = {&mockedModule};
    Composition composition(modules, 1);
    GameController controller;
    GameState state;
    engine = new GameEngine(composition, controller, state);
    engine->setup();
}

void loop() {
    engine->loop();
}
