#include "composition.h"
#include "modules/move.h"
#include "modules/score.h"

void compose()
{
    MoveModule* moveModule = new MoveModule();
    ScoreModule* scoreModule = new ScoreModule();

    modules[moveUp] = moveModule;
    modules[moveDown] = moveModule;
    modules[scored] = scoreModule;
    modules[errorInvalidInput] = moveModule;
}
