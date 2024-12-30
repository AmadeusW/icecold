#include "composition.h"

class Composition {
    public:
        Composition(); // todo: pass in a list of Module objects
        void setupAll(GameState& state); // call setup method on each module object
        void getInput(GameState& state); // call getInput method on each module
        void setOuput(GameState& state); // call setOuput method on each module
};
