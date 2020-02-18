#include "composition.h"
#include "modules/move.h"
#include "modules/score.h"

Module* modules[MAX_State];

void compose()
{
    MoveModule* moveModule = new MoveModule();
    ScoreModule* scoreModule = new ScoreModule();

    modules[idle] = moveModule;
    modules[moveUp] = moveModule;
    modules[moveDown] = moveModule;
    modules[scored] = scoreModule;
    modules[errorInvalidInput] = moveModule;
}

Module* getModule(State state)
{
    return modules[state];
}
