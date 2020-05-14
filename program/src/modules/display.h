#ifndef display_h
#define display_h

#include "../module.h"

class Display : public Module {
    int level;
    int health;
    void TestSequence();
    public:
        virtual void Setup();
        virtual void Read();
        void SetLevel(int level);
        void SetHealth(int health);
        void Write();
};

#endif