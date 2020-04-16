#include "Arduino.h"
#include "state.h"
#include "pins.h"

// Define externs declared in pins.h
bool joyAUp;
bool joyADown;

void setupPins()
{
  // Responsibility of Input module
  pinMode(SensorJoyAUp, INPUT);
  pinMode(SensorJoyADown, INPUT);
  pinMode(SensorBallDown, INPUT);
  // Responsibility of BallRelease module
  pinMode(PinServo, OUTPUT);
}

void readPins()
{
  // This should be responsibility of Input module
  joyAUp = digitalRead(SensorJoyAUp) == HIGH;
  joyADown = digitalRead(SensorJoyADown) == HIGH;


  Serial.print("T");
  Serial.print(turn);
  Serial.print(". S");
  Serial.print(state);
  Serial.print(". pins ");
  Serial.print(joyAUp);
  Serial.print(joyADown);
  Serial.println(".");
}
