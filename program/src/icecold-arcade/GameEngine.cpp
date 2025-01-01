#include "composition.h"
#include "GameController.h"
#include "GameEngine.h"
#include "GameState.h"

GameEngine::GameEngine(
    Composition& composition,
    GameController& controller,
    GameState& state
):
    state(state),
    composition(composition),
    controller(controller)
{}

void GameEngine::setup() {
    composition.setupAll(state);
    controller.setup(state);
}

void GameEngine::loop() {
    composition.getInput(state);
    controller.updateState(state);
    composition.setOutput(state);
}
