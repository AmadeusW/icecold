// Entry point for the code running on the microcontroller

#include "composition.h"
#include "GameController.h"
#include "GameEngine.h"
#include "GameState.h"

#include "module.h"
#include "modules/LedModule.h"

GameEngine* engine;

void setup() {
    // Example usage
    LedModule ledModule1(13);
    LedModule ledModule2(14);
    Module* modules[] = {&ledModule1, &ledModule2};
    Composition composition(modules, 2);
    GameController controller;
    GameState state;
    engine = new GameEngine(composition, controller, state);
    engine->setup();
}

void loop() {
    engine->loop();
}
