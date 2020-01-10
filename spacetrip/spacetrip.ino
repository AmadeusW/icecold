#include "pins.h"
//<include "future.h"

void setup()
{
   setupPins();
   startMotor();
}

void loop()
{
   brake();
   delay(1000);

   move(true);

   brake();
   delay(1000);

   move(false);
}

void startMotor()
{
   digitalWrite(STBY, HIGH);
}

void brake()
{
   digitalWrite(LED, LOW);
   digitalWrite(AIN1, HIGH);
   digitalWrite(AIN2, HIGH);
}

void move(bool up)
{
   digitalWrite(LED, HIGH);
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
   
   analogWrite(PWMA, 30);
   delay(500);
   analogWrite(PWMA, 40);
   delay(500);
   analogWrite(PWMA, 50);
   delay(500);
   analogWrite(PWMA, 60);
   delay(500);
   analogWrite(PWMA, 70);
   delay(500);
}
