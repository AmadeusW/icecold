#include "composition.h"

class Composition {
    public:
        // Constructor taking initializer list for easier module initialization
        Composition(std::initializer_list<Module*> moduleList) : module_count(0) {
            for (Module* module : moduleList) {
                if (module_count < MAX_MODULES) {
                    modules[module_count++] = module;
                }
            }
        }

        // Constructor taking array of modules and count
        Composition(Module** moduleArray, int count) : module_count(0) {
            for (int i = 0; i < count && i < MAX_MODULES; i++) {
                modules[module_count++] = moduleArray[i];
            }
        }

        // Delete copy constructor and assignment operator
        // to prevent accidental copying of module pointers
        Composition(const Composition&) = delete;
        Composition& operator=(const Composition&) = delete;

        void setupAll(GameState& state)
        {
            // call setup method on each module object
            for (int i = 0; i < module_count; i++)
            {
                modules[i]->setup(state);
            }
        }

        void getInput(GameState& state)
        {
            // call getInput method on each module
            for (int i = 0; i < module_count; i++)
            {
                modules[i]->getInput(state);
            }
        }

        void setOuput(GameState& state)
        {
            // call setOuput method on each module
            for (int i = 0; i < module_count; i++)
            {
                modules[i]->setOutput(state);
            }
        }
        
    Module* modules[MAX_MODULES];
    int module_count;
};
