#ifndef motor_h
#define motor_h

#include "../module.h"

class Motor : public Module {
    public:
        virtual void Setup();
        virtual void Read();
        void Brake();
        void Move(bool up, int speed);
};

#endif