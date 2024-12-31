#include "composition.h"
#include "GameController.h"
#include "GameEngine.h"
#include "GameState.h"

class GameEngine {
    private:
        GameState& state;
        Composition& composition;
        GameController& controller;

    public:
        GameEngine(
            Composition& composition,
            GameController& controller,
            GameState& state
        ):
            state(state),
            composition(composition),
            controller(controller)
        {}

        void setup() {
            composition.setupAll(state);
            controller.setup(state);
        }

        void loop() {
            composition.getInput(state);
            controller.updateState(state);
            composition.setOutput(state);
        }
};
