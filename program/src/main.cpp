#include "Arduino.h"
#include "pins.h"
#include "module.h"
#include "state.h"
#include "composition.h"

// extern variables declared in state.h
// define them here and initialize in setup()
State state;
int turn;
bool freezeState;
int unfreezeTurn;

void setup()
{
  state = uninitialized;
  turn = 0;
  freezeState = false;
  unfreezeTurn = 0;

  setupPins(); // Pins are set up and read separately
  compose(); // Compose all modules

  // Setup all modules
  for (int stateId = 0; stateId < (int)MAX_State; stateId++)
  {
    Module* module = getModule((State)stateId);
    if (module == 0)
    {
        Serial.print("No setup for ");
        Serial.println(stateId);
    }
    else
    {
        Serial.print("Setup ");
        Serial.println(stateId);
        module->setup();
    }
  }

  Serial.begin(9600); // set up debugging
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
  Module* module = getModule(state);
  if (module == 0)
  {
    Serial.print("Write: no handler for ");
    Serial.println(state);
  }
  else
  {
    Serial.print("Write: ");
    Serial.println(state);
    module->work(state);
  }
}

void displayState()
{
  Module* module = getModule(state);
  if (module == 0)
  {
    Serial.print("Display: no handler for ");
    Serial.println(state);
  }
  else
  {
    Serial.print("Display: ");
    Serial.println(state);
    module->debug(state);
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
