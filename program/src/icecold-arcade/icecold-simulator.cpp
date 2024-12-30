// Entry point for the code running in the simulator

#include "composition.h"
#include "GameController.h"
#include "GameEngine.h"
#include "GameState.h"

GameEngine engine;

void setup() {
    Composition composition = new Composition(); // pass the simulator module
    GameController controller = new GameController();
    GameState state = new GameState();
    engine = new GameEngine(composition, state, controller);
    engine.setup();
}

void loop() {
    engine.loop();
}
