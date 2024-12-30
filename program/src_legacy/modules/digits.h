#ifndef digits_h
#define digits_h

#include "../module.h"

class Adafruit_7segment;

class Digits : public OutputModule {
    Adafruit_7segment* matrix;
    int value;
    public:
        virtual void Setup();
        virtual void Output(int tick);
        void SetValue(int value);
};

#endif