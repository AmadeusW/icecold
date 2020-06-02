#ifndef range_h
#define range_h

#include "../module.h"

class VL53L0X;

class Range : public Module {
    VL53L0X* sensor; // TODO: left and right sensors
    int value;
    public:
        virtual void Setup();
        virtual void Read();
        int GetValue(); // TODO: left or right?
};

#endif