#include "composition.h"
#include "handlers/defaultHandler.h"
#include "handlers/scoreHandler.h"

Handler* handlers[MAX_State];

void Composition::compose()
{
    // why can't I use "new" x?
    //DefaultHandler DefaultHandler;
    //ScoreHandler ScoreHandler;
    DefaultHandler* defaultH = new DefaultHandler();
    ScoreHandler* scopeH = new ScoreHandler();

    handlers[idle] = defaultH;
    handlers[moveUp] = defaultH;
    handlers[moveDown] = scopeH;
    handlers[scored] = scopeH;
    handlers[errorInvalidInput] = defaultH;
}

Handler* Composition::getHandler(State state)
{
    return handlers[state];
}
