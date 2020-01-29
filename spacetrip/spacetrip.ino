#include "pins.h"
//<include "future.h"

void setup()
{
   setupPins();
   startMotor();
   Serial.begin(9600); // set up debugging
}

void loop()
{
   readSensors();
   move();
}

bool joyAUp = false;
bool joyADown = false;

void readSensors()
{
   joyAUp = digitalRead(SensorJoyAUp) == HIGH;
   joyADown = digitalRead(SensorJoyADown) == HIGH;

   //Serial.print("Up: ");
   //Serial.print(joyAUpAnalog);
   //Serial.print(" = ");
   Serial.print(joyAUp);
   //Serial.print(", ");
   //Serial.print("Down: ");
   //Serial.print(joyADownAnalog);
   //Serial.print(" = ");
   Serial.println(joyADown);
   //Serial.println("---");
}

void move()
{
   if (joyAUp && joyADown)
   {
      // Error condition
      brake();
   }
   else if (joyAUp)
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
   delay(50);
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
   analogWrite(PWMA, 255);
}
