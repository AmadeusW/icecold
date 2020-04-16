#include "Arduino.h"
#include "state.h"
#include "pins.h"

// Define externs declared in pins.h
bool joyAUp;
bool joyADown;
bool isBallDown;
bool isBallOnTarget;

void setupPins()
{
  // Responsibility of Debugger module
  pinMode(LED, OUTPUT);
  // Responsibility of Motor module
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(STBY, OUTPUT);
  // Responsibility of Input module
  pinMode(SensorJoyAUp, INPUT);
  pinMode(SensorJoyADown, INPUT);
  pinMode(SensorBallDown, INPUT);
  // Responsibility of BallRelease module
  pinMode(PinServo, OUTPUT);
  // Responsibility of ScoreSensor module
  pinMode(PinTarget, OUTPUT);
  pinMode(SensorScore, INPUT);
}

void readPins()
{
  // This should be responsibility of Input module
  joyAUp = digitalRead(SensorJoyAUp) == HIGH;
  joyADown = digitalRead(SensorJoyADown) == HIGH;
  // This should be responsibility of ScoreSensor module
  isBallDown = digitalRead(SensorBallDown) == HIGH;
  isBallOnTarget = digitalRead(SensorScore) == HIGH;

  Serial.print("T");
  Serial.print(turn);
  Serial.print(". S");
  Serial.print(state);
  Serial.print(". pins ");
  Serial.print(joyAUp);
  Serial.print(joyADown);
  Serial.print(isBallDown);
  Serial.print(isBallOnTarget);
  Serial.println(".");
}
