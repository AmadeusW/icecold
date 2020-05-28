#ifndef pins_h
#define pins_h

#include "Arduino.h"

#define SensorJoyAUp 4 // green
#define SensorJoyADown 5 // yellow
#define SensorJoyBUp 6 // blue
#define SensorJoyBDown 7 // yellow
#define OutputSerialClock 8 // orange
#define OutputSerialLatch 9 // orange
#define SensorBallAtTarget 10 // white
#define SensorBallAtBottom 11 // red
#define OutputSerialData 12 // green

#define PinServo 6

extern bool joyAUp;
extern bool joyADown;

void setupPins();
void readPins();

#endif
