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

  Serial.print("[");
  Serial.print(turn);
  Serial.print("] ");
  switch (state) {
    case uninitialized:     Serial.print("LOADIN"); break;
    case idle:              Serial.print(" idle "); break;
    case moveUp:            Serial.print(" up   "); break;
    case moveDown:          Serial.print(" down "); break;
    case errorInvalidInput: Serial.print("invald"); break;
    case scored:            Serial.print("scored"); break;
    case lost:              Serial.print(" lost "); break;
    default:                Serial.print("ERROR "); break;
  }
  Serial.print(state);
  Serial.print(" pins:");
  Serial.print(joyAUp);
  Serial.print(joyADown);
  Serial.println(".");
}
