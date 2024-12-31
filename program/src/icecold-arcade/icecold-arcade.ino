// Entry point for the code running on the microcontroller

#include "composition.h"
#include "GameController.h"
#include "GameEngine.h"
#include "GameState.h"

#include "modules/LedModule.h"

GameEngine engine;

void setup() {
    // Example usage
    LedModule ledModule1(13);
    LedModule ledModule2(14);

    Composition composition{&ledModule1, &ledModule2};
    GameController controller;
    GameState state;
    GameEngine engine(composition, controller, state);
    engine.setup();
}

void loop() {
    engine.loop();
}
