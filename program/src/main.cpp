#include "Arduino.h"
#include "pins.h"
#include "handler.h"
#include "state.h"
#include "composition.h"
#include "modules/motor.h"

// Define externs declared in state.h
State state = uninitialized;
int turn = 0;
bool freezeState = false;
int unfreezeTurn = 0;
Composition composition;
Motor motor;

void setup()
{
  Serial.begin(9600); // set up debugging
  Serial.print("Hello World");

  Serial.println("Setting up pins...");
  setupPins(); // Pins are set up and read separately
  digitalWrite(LED, HIGH);
  Serial.println("Composing handlers...");
  composition.compose(); // Compose all modules

  // Setup all modules
  motor.setup();
  // Setup all handlers
  for (int stateId = 0; stateId < (int)MAX_State; stateId++)
  {
    Handler* handler = composition.getHandler((State)stateId);
    if (handler == 0)
    {
      Serial.print("No setup for ");
      Serial.print(stateId);
      Serial.println(".");
    }
    else
    {
      Serial.print("Setting up handler ");
      Serial.print(stateId);
      Serial.println("...");
      handler->setup();
    }
  }

  Serial.println("Setup complete.");
  delay(50);
  digitalWrite(LED, LOW);
  state = idle; // running
}

void updateState()
{
   if (freezeState && turn < unfreezeTurn)
   {
      return;
   }
   if (isScoring)
   {
      state = scored;
   }
   else if (joyAUp && joyADown)
   {
      state = errorInvalidInput; // stop, error: invalid input
   }
   else if (joyAUp)
   {
      state = moveUp;
   }
   else if (joyADown) // TODO: add another angle limiter
   {
      state = moveDown;
   }
   else
   {
      state = idle;
   }
}

void writePins()
{
  Handler* handler = composition.getHandler(state);
  if (handler == 0)
  {
    Serial.print("Move: no handler for ");
    Serial.println(state);
  }
  else
  {
    Serial.print("Move: ");
    Serial.println(state);
    handler->move(state, motor);
  }
}

void displayState()
{
  Handler* handler = composition.getHandler(state);
  if (handler == 0)
  {
    Serial.print("Display: no handler for ");
    Serial.println(state);
  }
  else
  {
    Serial.print("Display: ");
    Serial.println(state);
    handler->debug(state);
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
   writePins();
   displayState();
   finishTurn();
}
