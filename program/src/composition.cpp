#include "composition.h"
#include "modules/move.c"
#include "modules/score.c"

void compose()
{
    modules[moveUp] = moveDispatcher;
    modules[moveDown] = moveDispatcher;
    modules[scored] = scoreDispatcher;
    modules[errorInvalidInput] = moveDispatcher;
}
