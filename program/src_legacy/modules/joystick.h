#ifndef joystick_h
#define joystick_h

#include "../module.h"

class Joystick : public InputModule {
    int leftDirection;
    int rightDirection;
    public:
        virtual void Setup();
        virtual void Input();
        int GetLeftDirection();
        int GetRightDirection();
};

#endif