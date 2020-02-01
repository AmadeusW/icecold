#include "pins.h"
//<include "future.h"
#include <Servo.h>

Servo ballServo;
bool joyAUp = false;
bool joyADown = false;
bool isScoring = false;

void setup()
{
   setupPins();
   startMotor();
   ballServo.attach(BallServo);
   Serial.begin(9600); // set up debugging
}

void loop()
{
   readSensors();
   act();
}

void readSensors()
{
   joyAUp = digitalRead(SensorJoyAUp) == HIGH;
   joyADown = digitalRead(SensorJoyADown) == HIGH;
   isScoring = digitalRead(SensorScored) == HIGH;

   //Serial.print("Up: ");
   //Serial.print(joyAUpAnalog);
   //Serial.print(" = ");
   Serial.print(joyAUp);
   //Serial.print(", ");
   //Serial.print("Down: ");
   //Serial.print(joyADownAnalog);
   //Serial.print(" = ");
   Serial.print(joyADown);
   Serial.println(isScoring);
   //Serial.println("---");
}

void act()
{
   if (isScoring)
   {
      score();
   }
   if (joyAUp && joyADown)
   {
      // Error condition
      brake();
      debugMessage(1);
   }
   else if (joyAUp)
   {
      digitalWrite(LED, HIGH);
      move(true, 255);
   }
   else if (joyADown) // TODO: add another angle limiter
   {
      digitalWrite(LED, HIGH);
      move(false, 255);
   }
   else
   {
      brake();
   }
   delay(50);
   digitalWrite(LED, LOW);
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

void score()
{
   analogWrite(BallServo, 10);
   for (int i = 0; i < 5; i++)
   {
      digitalWrite(LED, LOW);
      move(false, 50);
      delay(100);
      digitalWrite(LED, HIGH);
      move(false, 50);
      delay(100);
   }
   brake();
   ballServo.write(160);
   delay(1000);
   Serial.print("B");
   digitalWrite(LED, HIGH);
   ballServo.write(20);
   delay(1000);
   Serial.println("C");
   digitalWrite(LED, LOW);
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

void debugMessage(int code)
{
  for (int i = 0; i < code; i++)
  {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }
  delay(300);  
}
