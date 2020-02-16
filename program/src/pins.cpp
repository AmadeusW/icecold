#ifndef pins_c
#define pins_c

#include "Arduino.h"
#include "state.h"
#include "pins.h"

void setupPins()
{
  pinMode(LED, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(SensorJoyAUp, INPUT);
  pinMode(SensorJoyADown, INPUT);
  pinMode(SensorScored, INPUT);
  pinMode(PinServo, OUTPUT);
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

#endif
