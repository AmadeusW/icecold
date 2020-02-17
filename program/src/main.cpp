#include "Arduino.h"
#include "pins.h"
#include "module.h"
#include "state.h"
#include "composition.h"

// Define externs declared in state.h
State state = uninitialized;
int turn = 0;
bool freezeState = false;
int unfreezeTurn = 0;

void setup()
{
  Serial.begin(9600); // set up debugging
  Serial.print("Hello World");

  Serial.println("Setting up pins...");
  setupPins(); // Pins are set up and read separately
  digitalWrite(LED, HIGH);
  Serial.println("Composing modules...");
  compose(); // Compose all modules

  // Setup all modules
  for (int stateId = 0; stateId < (int)MAX_State; stateId++)
  {
    Module* module = getModule((State)stateId);
    if (module == 0)
    {
      Serial.print("No setup for ");
      Serial.print(stateId);
      Serial.println(".");
    }
    else
    {
      Serial.print("Setting up module ");
      Serial.print(stateId);
      Serial.println("...");
      module->setup();
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
