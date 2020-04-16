#ifndef scoresensor_h
#define scoresensor_h

#include "../module.h"

class ScoreSensor : public Module {
    bool isBallOnTarget;
    bool isBallDown;
    public:
        virtual void Setup();
        virtual void Read();
        void SetTarget(bool enabled);
        bool IsScoring();
        bool IsLosing();
};

#endif