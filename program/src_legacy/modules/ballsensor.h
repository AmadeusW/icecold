#ifndef ballsensor_h
#define ballsensor_h

#include "../module.h"

class BallSensor : public InputModule {
    bool isBallOnTarget;
    bool isBallDown;
    public:
        virtual void Setup();
        virtual void Input();
        bool IsDown();
        bool IsOnTarget();
};

#endif