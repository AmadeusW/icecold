#ifndef display_h
#define display_h

#include "../module.h"

class Display : public Module {
    int score;
    public:
        virtual void Setup();
        virtual void Read();
        void SetScore(int score);
        void Write();
};

#endif