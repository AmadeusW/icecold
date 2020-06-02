#ifndef range_h
#define range_h

#include "../module.h"

class Range : public Module {
    int value;
    public:
        virtual void Setup();
        virtual void Read();
        int GetValue(); // TODO: left or right?
};

#endif