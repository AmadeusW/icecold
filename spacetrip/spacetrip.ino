#include <Servo.h>

#include "pins.h"
//<include "future.h"

Servo ballServo;
bool joyAUp = false;
bool joyADown = false;
bool isScoring = false;
int state = 0;
int turn = 0;
bool freezeState = false;
int unfreezeTurn = 0;

void setup()
{
   setupPins();
   startMotor();
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
      state = 40; // Scoring
   }
   else if (joyAUp && joyADown)
   {
      state = 11; // stop, error: invalid input
      brake();
   }
   else if (joyAUp)
   {
      state = 20; // Up
   }
   else if (joyADown) // TODO: add another angle limiter
   {
      state = 30; // Down
   }
   else
   {
      state = 10; // stop
      brake();
   }
}

void writePins()
{
   switch (state)
   {
      case 20: // Up
         move(true, 255);
         return;
      case 30: // Down
         move(false, 255);
         return;
      case 40: // Scored
         ballServo.write((unfreezeTurn - turn) * 8);
      case 10: // No input
      case 11: // Invalid input
      default:
         brake();
         return;
   }
}

void writeDebug()
{
   switch (state)
   {
      case 20: // Up
      case 30: // Down
         digitalWrite(LED, HIGH);
         return;
      case 40:
         digitalWrite(LED, turn % 3 == 0 ? HIGH : LOW);
         return;
      case 11: // Invalid input
         digitalWrite(LED, turn % 2 == 0 ? HIGH : LOW);
         return;
   }
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
