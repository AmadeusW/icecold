#ifndef composition_h
#define composition_h

#include "module.h"
#include <initializer_list>
const int MAX_MODULES = 10;

class Composition {
    public:
        Composition(std::initializer_list<Module*> moduleList);
        void setupAll(GameState& state);
        void getInput(GameState& state);
        void setOutput(GameState& state);

    private:
        Module* modules[MAX_MODULES];
        int module_count;
};

#endif