// Entry point for the code running on the microcontroller

#include "../common/composition.h"
#include "../common/GameController.h"
#include "../common/GameEngine.h"
#include "../common/GameState.h"

#include "../common/module.h"
#include "../common/modules/LedModule.h"

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

int main()
{
    setup();
    while (true) {
        loop();
    }
}
