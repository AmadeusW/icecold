#ifndef digits_h
#define digits_h

#include "../module.h"

class Adafruit_7segment;

class Digits : public Module {
    Adafruit_7segment* matrix;
    int value;
    public:
        virtual void Setup();
        virtual void Read();
        void SetValue(int value);
        void Write();
};

#endif