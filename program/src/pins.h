#ifndef pins_h
#define pins_h

#include "Arduino.h"

#define SensorAngle 0
#define SensorLost 0
#define SensorBallDown 7
#define SensorJoyAUp 4
#define SensorJoyADown 5
#define SensorJoyBUp 0
#define SensorJoyBDown 0

#define PinServo 6

extern bool joyAUp;
extern bool joyADown;

void setupPins();
void readPins();

#endif
