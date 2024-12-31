// Example module implementation
#ifndef LED_MODULE_H
#define LED_MODULE_H

#include "../module.h"
#include "Arduino.h"

class LedModule : public Module {
public:
    LedModule(int pin) : pin_(pin) {}

    void setup(GameState& state) override {
        pinMode(pin_, OUTPUT);
    }

    void getInput(GameState& state) override {
        // LEDs don't have input
    }

    void setOutput(GameState& state) override {
        // Example: use game state to determine LED state
        bool shouldBeOn = state.isLedActive();  // assumes this method exists
        digitalWrite(pin_, shouldBeOn ? HIGH : LOW);
    }

private:
    int pin_;
};

#endif
