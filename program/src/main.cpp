#include "Arduino.h"
#include "pins.h"
#include "handler.h"
#include "state.h"
#include "composition.h"
#include "modules/motor.h"

// Define externs declared in state.h
State state = uninitialized;
int turn = 0;
Composition composition;

void setup()
{
  Serial.begin(9600); // set up debugging
  Serial.print("Hello World");

  Serial.println("Setting up pins...");
  setupPins(); // Pins are set up and read separately
  digitalWrite(LED, HIGH);
  Serial.println("Composing modules...");
  composition.Compose(); // Compose modules and handlers
  Serial.println("Setting up modules...");
  composition.Setup(); // Setup all modules and handlers
  Serial.println("Setup complete.");
  delay(50);
  digitalWrite(LED, LOW);
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

void act()
{
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
    delay(50);
    digitalWrite(LED, LOW);
    turn++;
}

void loop()
{
    readPins();
    updateState();
    act();
    finishTurn();
}
