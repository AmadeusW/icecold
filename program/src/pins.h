#ifndef pins_h
#define pins_h

#include "Arduino.h"

#define AIN1 1
#define AIN2 2
#define PWMA 3
#define STBY 0
#define LED 13

#define SensorAngle 0
#define SensorLost 0
#define SensorBallDown 7
#define SensorJoyAUp 4
#define SensorJoyADown 5
#define SensorJoyBUp 0
#define SensorJoyBDown 0

#define PinServo 6

#define PinTarget 10
#define SensorScore 11

extern bool joyAUp;
extern bool joyADown;
extern bool isBallDown;
extern bool isBallOnTarget;

void setupPins();
void readPins();

#endif
