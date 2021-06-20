#include "Arduino.h"
#include "pins.h"
#include "handler.h"
#include "state.h"
#include "composition.h"

// Define externs declared in state.h
State state = uninitialized;
int turn = 0;
Composition composition;

void setup()
{
  Serial.begin(115200); // set up debugging
  while (! Serial) { delay(1); }
  Serial.println("Hello World!");

  Serial.println("Composing modules...");
  composition.Compose(); // Compose modules and handlers
  Serial.println("Setting up modules...");
  composition.Setup(); // Setup all modules and handlers
  Serial.println("Setup complete.");
  delay(50);
  state = idle; // running
}

void updateState()
{
    Handler* handler = composition.GetHandler(state);
    if (handler == 0)
    {
        Serial.print("UpdateState: no handler for ");
        Serial.println(state);
    }
    else
    {
        state = handler->SetState(state, turn);
    }
}

void printCurrentState()
{
    Serial.printf("[%d]", turn);
    switch (state) {
        case uninitialized:      Serial.print("uninit"); break;
        case newGame:            Serial.print(" new "); break;
        case shooter:            Serial.print("shoot "); break;
        case playfield:          Serial.print(" play "); break;
        case outlane:            Serial.print(" out  "); break;
        case gameOverWon:        Serial.print(" won  "); break;
        case gameOverLost:       Serial.print(" lost "); break;
        default:                 Serial.print("ERROR "); break;
    }
}

void act()
{
    printCurrentState();

    Handler* handler = composition.GetHandler(state);
    if (handler == 0)
    {
        Serial.print("Act: no handler for ");
        Serial.println(state);
    }
    else
    {
        handler->Act(state, turn);
    }
}

void finishTurn()
{
    delay(50); // TODO: delay as many ms as necessary to achieve 50ms per turn
    turn++;
}

void loop()
{
    composition.Input();
    updateState();
    act();
    finishTurn();
}
