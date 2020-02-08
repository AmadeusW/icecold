#include "Arduino.h"
#include <Servo.h>
#include "pins.h"
#include "state.h"

void setup()
{
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop()
{
  digitalWriteFast(LED_BUILTIN,!digitalReadFast(LED_BUILTIN));
  delay(500);
  delay(PWMA);
}
