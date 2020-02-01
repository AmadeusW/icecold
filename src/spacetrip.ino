#include <Servo.h>

#include "pins.h"
//<include "future.h"

enum States {
   uninitialized = 0,
   idle,
   moveUp,
   moveDown,
   errorInvalidInput,
   scored, // TODO: add multiple stages for scored
   MAXState
};

Servo ballServo;
bool joyAUp = false;
bool joyADown = false;
bool isScoring = false;
int state = 0;
int turn = 0;
bool freezeState = false;
int unfreezeTurn = 0;
int (*debugHandlers[MAXState]) (bool);

void setup()
{
   setupPins();
   startMotor();
   debugHandlers[moveUp] = debugMovement;
   debugHandlers[moveDown] = debugMovement;
   debugHandlers[scored] = debugScored;
   debugHandlers[errorInvalidInput] = debugInvalidInput;
   ballServo.attach(BallServo);
   Serial.begin(9600); // set up debugging
   state = 1; // running
}

void loop()
{
   readPins();
   updateState();
   writePins();
   writeDebug();
   finishTurn();
}

void readPins()
{
  joyAUp = digitalRead(SensorJoyAUp) == HIGH;
  joyADown = digitalRead(SensorJoyADown) == HIGH;
  isScoring = digitalRead(SensorScored) == HIGH;

  Serial.print("T");
  Serial.print(turn);
  Serial.print(". S");
  Serial.print(state);
  Serial.print(". pins ");
  Serial.print(joyAUp);
  Serial.print(joyADown);
  Serial.println(isScoring);
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
   switch (state)
   {
      case moveUp: // Up
         move(true, 255);
         return;
      case moveDown: // Down
         move(false, 255);
         return;
      case scored: // Scored
         ballServo.write((unfreezeTurn - turn) * 8);
      case idle: // No input
      case errorInvalidInput: // Invalid input
      default:
         brake();
         return;
   }
}

void writeDebug()
{
   int (*handler)(bool);
   handler = (*debugHandlers[state]);
   if (handler == 0)
   {
      Serial.print("No handler for ");
      Serial.println(state);
   }
   else
   {
      Serial.print("Calling handler for ");
      Serial.println(state);
      handler(false);
   }
}

int debugMovement(bool action)
{
   if (!action)
      digitalWrite(LED, HIGH);
   return 0;
}

int debugScored(bool action)
{
   if (!action)
      digitalWrite(LED, turn % 2 == 0 && turn % 6 != 0 ? HIGH : LOW);
   return 0;
}

int debugInvalidInput(bool action)
{
   if (!action)
      digitalWrite(LED, turn % 2 == 0 ? HIGH : LOW);
   return 0;
}

void finishTurn()
{
   delay(50);
   digitalWrite(LED, LOW);
   turn++;
}

void startMotor()
{
   digitalWrite(STBY, HIGH);
}

void brake()
{
   digitalWrite(AIN1, HIGH);
   digitalWrite(AIN2, HIGH);
}

void move(bool up, int speed)
{
   if (up)
   {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);  
   }
   else
   {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
   }
   analogWrite(PWMA, speed);
}
