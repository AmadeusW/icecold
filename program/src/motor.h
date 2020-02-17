#ifndef motor_h
#define motor_h

extern void motorSetup();
extern void motorBrake();
extern void motorMove(bool up, int speed);

#endif