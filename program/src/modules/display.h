#ifndef display_h
#define display_h

#include "../module.h"

class Display : public OutputModule {
    int level;
    int health;
    public:
        virtual void Setup();
        virtual void Output(int tick);
        void SetLevel(int level);
        void SetHealth(int health);
        void Test();
};

#endif