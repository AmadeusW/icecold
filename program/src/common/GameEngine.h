#ifndef GameEngine_h
#define GameEngine_h

class Composition;
class GameController;
class GameState;

class GameEngine {
    private:
        Composition& composition;
        GameController& controller;
        GameState& state;

    public:
        GameEngine(
            Composition& composition,
            GameController& controller,
            GameState& state
        );
        void setup();
        void loop();
};

#endif