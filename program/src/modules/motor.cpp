#include "Arduino.h"
#include "motor.h"
#include "../pins.h"

void Motor::setup()
{
   digitalWrite(STBY, HIGH);
}

void Motor::brake()
{
   digitalWrite(AIN1, HIGH);
   digitalWrite(AIN2, HIGH);
}

void Motor::move(bool up, int speed)
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
