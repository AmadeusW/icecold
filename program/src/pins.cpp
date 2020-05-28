#include "Arduino.h"
#include "state.h"
#include "pins.h"

// Define externs declared in pins.h
bool joyAUp;
bool joyADown;

void setupPins()
{
  // Responsibility of Input module
  pinMode(PinJoyAUp, INPUT);
  pinMode(PinJoyADown, INPUT);
  pinMode(PinJoyBUp, INPUT);
  pinMode(PinJoyBDown, INPUT);
  pinMode(PinBallAtTarget, INPUT);
  pinMode(PinBallAtBottom, INPUT);
}

void readPins()
{
  // This should be responsibility of Input module
  joyAUp = digitalRead(PinJoyAUp) == HIGH;
  joyADown = digitalRead(PinJoyADown) == HIGH;
  bool joyBUp = digitalRead(PinJoyBUp) == HIGH;
  bool joyBDown = digitalRead(PinJoyBDown) == HIGH;
  bool ballAtTarget = digitalRead(PinBallAtTarget) == HIGH;
  bool ballAtBottom = digitalRead(PinBallAtBottom) == HIGH;

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
  Serial.print(joyBUp);
  Serial.print(joyBDown);
  Serial.print(ballAtTarget);
  Serial.print(ballAtBottom);
  Serial.println(".");
}
