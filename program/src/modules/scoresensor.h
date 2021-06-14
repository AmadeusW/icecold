#ifndef scoresensor_h
#define scoresensor_h

#include "../module.h"

class ScoreSensor : public InputModule {
    bool isBallOnTarget;
    bool isBallDown;
    public:
        virtual void Setup();
        virtual void Input();
        bool IsScoring();
        bool IsLosing();
};

#endif