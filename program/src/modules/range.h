#ifndef range_h
#define range_h

#include "../module.h"

class Range : public InputModule {
    int value0;
    int value1;
    bool initialized0;
    bool initialized1;
    public:
        virtual void Setup();
        virtual void Input();
        int GetValue(int module);
};

#endif