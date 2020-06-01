#ifndef digits_h
#define digits_h

#include "../module.h"

class Digits : public Module {
    int value;
    public:
        virtual void Setup();
        virtual void Read();
        void SetValue(int value);
        void Write();
};

#endif