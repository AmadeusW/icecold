#ifndef motor_h
#define motor_h

#include "../module.h"

class Motor : public OutputModule {
    int speedLeft;
    int speedRight;
    public:
        virtual void Setup();
        virtual void Output(int tick);
        void Brake();
        void MoveLeft(bool up, int speed);
        void MoveRight(bool up, int speed);
};

#endif