#include "Arduino.h"
#include "../lib/Servo/Servo.h"
#include "../state.h"
#include "../pins.h"

Servo ballServo;

int scoreDispatcher(int method)
{
    switch (method)
    {
        case METHOD_SETUP:
            scoreSetup();
        case METHOD_WORK:
            scoreWork();
        case METHOD_DEBUG:
            scoreDebug();
        default:
            return -1;
    }
    return 0;
}

void scoreSetup()
{
    ballServo.attach(PinServo);
}

void scoreWork()
{
    switch (state) {
        case scored:
            ballServo.write((unfreezeTurn - turn) * 8);
            return;
        case moveDown:
            move(false, 255);
            return;
        default:
            brake();
    }
}

void scoreDebug()
{
    switch (state) {
        case scored:
            digitalWrite(LED, turn % 2 == 0 && turn % 6 != 0 ? HIGH : LOW);
            return;
        default:
            return;
    }
}

#endif