#ifndef composition_h
#define composition_h

#include "module.h"
const int MAX_MODULES = 10;

class Composition {
    public:
        Composition(Module** moduleArray, int count);
        void setupAll(GameState& state);
        void getInput(GameState& state);
        void setOutput(GameState& state);
        // Delete copy constructor and assignment operator
        // to prevent accidental copying of module pointers
        Composition(const Composition&) = delete;
        Composition& operator=(const Composition&) = delete;


    private:
        Module* modules[MAX_MODULES];
        int module_count;
};

#endif