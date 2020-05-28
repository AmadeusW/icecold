#include "pins.h"

int lives = 10;
int level = 1;
bool resetting;

bool isAngleCritical;
bool isBallLost;
bool isPointScored;

bool joyAUp;
bool joyADown;
bool joyBUp;
bool joyBDown;

bool wasAngleCritical;
bool wasBallLost;
bool wasPointScored;

void startGame()
{

}

void futureLoop()
{
   readSensors();
   updateState();
   move();
   debounceSensors();
   displayState();
}

void readSensors()
{
   isAngleCritical = digitalRead(SensorAngle);
   isBallLost = digitalRead(SensorLost);
   isPointScored = digitalRead(SensorBallDown);
   joyAUp = digitalRead(PinJoyAUp);
   joyADown = digitalRead(PinJoyADown);
   joyBUp = digitalRead(PinJoyBUp);
   joyBDown = digitalRead(PinJoyBDown);
}

void updateState()
{
   if (isBallLost && !wasBallLost)
   {
      lives--;
      resetting = true;
   }
   if (isPointScored && !wasPointScored)
   {
      level++;
      resetting = true;
   }
   if (lives == 0)
   {
      resetting = true;
   }
   if (level == 10)
   {
      resetting = true;
   }
}

void debounceSensors()
{
   wasAngleCritical = isAngleCritical;
   wasBallLost = isBallLost;
   wasPointScored = isPointScored;
}

void move()
{
   if (resetting)
   {
      move(false); // move down
   }
   if (joyAUp)
   {
      move(true);
   }
   else if (joyADown)
   {
      move(false);
   }
   else
   {
      brake();
   }
}

void displayState()
{
   // display lives
   // display level
   // light up level LED
   // show score
}
