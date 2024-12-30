#ifndef GameEngine_h
#define GameEngine_h

class GameEngine {
    public:
        GameEngine(
            Composition& composition
            GameController& controller
            GameState& state
        );
        void setup();
        void loop();
};

#endif