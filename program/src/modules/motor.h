#ifndef motor_h
#define motor_h

class Motor /* add base class public Module */ {
    public:
        virtual void setup();
        virtual void brake();
        virtual void move(bool up, int speed);
};

#endif