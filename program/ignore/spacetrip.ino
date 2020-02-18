#include "pins.h"
#include "state.h"
#include "composition.h"
//<include "future.h"

void setup()
{
   state = uninitialized;
   setupPins(); // Pins are set up and read separately
   compose(); // Compose all modules

   // Setup all modules
   for (int stateId = 0; stateId < MAX_State; stateId++)
   {
      int (*dispatcher)(Methods) = (*modules[stateId]);
      if (dispatcher == 0)
      {
         Serial.print("No setup for ");
         Serial.println(state);
      }
      else
      {
         Serial.print("Setup ");
         Serial.println(state);
         dispatcher(METHOD_SETUP);
      }
   }

   Serial.begin(9600); // set up debugging
   state = idle; // running
}

void loop()
{
   readPins();
   updateState();
   writePins();
   displayState();
   finishTurn();
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
   int (*dispatcher)(Methods) = (*modules[state]);
   if (dispatcher == 0)
   {
      Serial.print("Write: no handler for ");
      Serial.println(state);
   }
   else
   {
      Serial.print("Write: ");
      Serial.println(state);
      dispatcher(METHOD_WORK);
   }
}

void displayState()
{
   int (*dispatcher)(Methods) = (*modules[state]);
   if (dispatcher == 0)
   {
      Serial.print("Display: no handler for ");
      Serial.println(state);
   }
   else
   {
      Serial.print("Display: ");
      Serial.println(state);
      dispatcher(METHOD_DEBUG);
   }
}

void finishTurn()
{
   delay(50);
   digitalWrite(LED, LOW);
   turn++;
}
