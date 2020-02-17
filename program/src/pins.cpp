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
