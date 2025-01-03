// Entry point for the code running in the simulator

#include <cstring>
#include <iostream>
#include <unistd.h>

#include "simulatorModule.h"
#include "../common/module.h"
#include "../common/composition.h"
#include "../common/GameController.h"
#include "../common/GameEngine.h"
#include "../common/GameState.h"

GameEngine* engine = nullptr;

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

int main() {
    try {
        setup();
        while(true) {
            loop();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
