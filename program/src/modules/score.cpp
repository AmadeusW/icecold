#include "Arduino.h"
#include "../lib/Servo/Servo.h"
#include "score.h"
#include "../composition.h"
#include "../state.h"
#include "../pins.h"

Servo ballServo;

void ScoreModule::setup()
{
    ballServo.attach(PinServo);
}

void ScoreModule::work(State state)
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

void ScoreModule::debug(State state)
{
    switch (state) {
        case scored:
            digitalWrite(LED, turn % 2 == 0 && turn % 6 != 0 ? HIGH : LOW);
            return;
        default:
            return;
    }
}
