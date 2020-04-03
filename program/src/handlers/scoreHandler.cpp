#include "Arduino.h"
#include "../lib/Servo/Servo.h"
#include "scoreHandler.h"
#include "../composition.h"
#include "../motor.h"
#include "../Handler.h"
#include "../pins.h"

Servo ballServo;

void ScoreHandler::setup()
{
    ballServo.attach(PinServo);
}

void ScoreHandler::work(State state)
{
    switch (state) {
        case scored:
            ballServo.write((unfreezeTurn - turn) * 8);
            return;
        case moveDown:
            motorMove(false, 255);
            return;
        default:
            motorBrake();
    }
}

void ScoreHandler::debug(State state)
{
    switch (state) {
        case scored:
            digitalWrite(LED, turn % 2 == 0 && turn % 6 != 0 ? HIGH : LOW);
            return;
        default:
            return;
    }
}
