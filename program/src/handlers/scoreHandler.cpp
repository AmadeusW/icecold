#include "Arduino.h"
#include "../lib/Servo/Servo.h"
#include "scoreHandler.h"
#include "../modules/motor.h"
#include "../composition.h"
#include "../Handler.h"
#include "../pins.h"

Servo ballServo;

void ScoreHandler::setup()
{
    ballServo.attach(PinServo);
}

void ScoreHandler::move(State state, Motor motor)
{
    switch (state) {
        case scored:
            ballServo.write((unfreezeTurn - turn) * 8);
            return;
        case moveDown:
            motor.move(false, 255);
            return;
        default:
            motor.brake();
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
