#include "composition.h"

Composition::Composition(Module** moduleArray, int count) : module_count(0) {
    for (int i = 0; i < count && i < MAX_MODULES; i++) {
        modules[module_count++] = moduleArray[i];
    }
}

void Composition::setupAll(GameState& state)
{
    // call setup method on each module object
    for (int i = 0; i < module_count; i++)
    {
        modules[i]->setup(state);
    }
}

void Composition::getInput(GameState& state)
{
    // call getInput method on each module
    for (int i = 0; i < module_count; i++)
    {
        modules[i]->getInput(state);
    }
}

void Composition::setOutput(GameState& state)
{
    // call setOuput method on each module
    for (int i = 0; i < module_count; i++)
    {
        modules[i]->setOutput(state);
    }
}
