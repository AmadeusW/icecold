#ifndef composition_h
#define composition_h

class Composition {
    public:
        Composition();
        void setupAll(GameState& state);
        void getInput(GameState& state);
        void setOuput(GameState& state);
};

#endif