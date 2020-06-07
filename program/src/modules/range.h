#ifndef range_h
#define range_h

#include "../module.h"

class Range : public Module {
    int value0;
    int value1;
    bool initialized0;
    bool initialized1;
    public:
        virtual void Setup();
        virtual void Read();
        int GetValue(int module);
};

#endif