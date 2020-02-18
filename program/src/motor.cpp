#include "Arduino.h"
#include "motor.h"
#include "pins.h"

void motorSetup()
{
   digitalWrite(STBY, HIGH);
}

void motorBrake()
{
   digitalWrite(AIN1, HIGH);
   digitalWrite(AIN2, HIGH);
}

void motorMove(bool up, int speed)
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
