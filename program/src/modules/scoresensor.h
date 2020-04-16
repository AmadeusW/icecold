#ifndef scoresensor_h
#define scoresensor_h

class ScoreSensor /* add base class public InputModule (reads pins) */ {
    public:
        virtual void setup();
        virtual void setTarget(bool enabled);
        virtual bool isScoring();
};

#endif