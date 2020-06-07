#ifndef pins_h
#define pins_h

#include "Arduino.h"

#define PinMotorAIn1 1
#define PinMotorAIn2 1
#define PinMotorPWMA 1
#define PinMotorSTBY 0
#define PinJoyAUp 4 // green
#define PinJoyADown 5 // yellow
#define PinJoyBUp 6 // blue
#define PinJoyBDown 7 // yellow
#define PinSerialClock 8 // orange
#define PinSerialLatch 9 // orange
#define PinBallAtTarget 10 // white
#define PinBallAtBottom 11 // red
#define PinSerialData 12 // green
#define PinDebugLed 13
#define PinRange0Enable 16 // Yellow
#define PinRange1Enable 17 // Yellow
#define PinI2CData 18 // White
#define PinI2CClock 19 // Orange
// Future:
// #define PinServo X

extern bool joyAUp;
extern bool joyADown;

void setupPins();
void readPins();

#endif
