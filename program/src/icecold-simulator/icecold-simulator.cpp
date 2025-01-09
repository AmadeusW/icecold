// Entry point for the code running in the simulator

#include <cstring>
#include <iostream>

#include "simulatorModule.h"
#include "../common/module.h"
#include "../common/composition.h"
#include "../common/GameController.h"
#include "../common/GameEngine.h"
#include "../common/GameState.h"

int main() {
    try {
        SimulatorModule simulatorModule{};
        Module* modules[] = {&simulatorModule};
        Composition composition(modules, 1);
        GameController controller;
        GameState state;
        GameEngine engine(composition, controller, state);

        engine.setup();
        while(true) {
            engine.loop();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
