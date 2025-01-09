#include <cstring>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#include "simulatorModule.h"
#include "virtual_serial.h"
#include "../common/module.h"
#include "../common/GameState.h"

VirtualSerialPort* virtualPort;

void SimulatorModule::setup(GameState& state) {
    // Create virtual serial port
    virtualPort = new VirtualSerialPort();
    std::cout << "Virtual Serial Port Created at: " << virtualPort->getPortPath() << std::endl;
    std::string statusMsg = "Simulator module: Setup\n";
    virtualPort->write(statusMsg);
}

void SimulatorModule::getInput(GameState& state) {
    std::string receivedData = virtualPort->read();
    if (!receivedData.empty()) {
        std::cout << "Received: " << receivedData << std::endl;
    } else
    {
        std::cout << "No input." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void SimulatorModule::setOutput(GameState& state) { 
    std::cout << "setOutput" << std::endl;
    std::string formattedState = serializeGameState(state);
    std::cout << formattedState << "\n" << std::endl;
    virtualPort->write(formattedState);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

std::string SimulatorModule::serializeGameState(GameState& state) {
    std::ostringstream oss;

    // Serialize GameMode as an integer
    oss << "mode=" << static_cast<int>(state.mode) << ";";

    // Serialize game state variables
    oss << "tick=" << state.tick << ";";
    oss << "balls=" << state.balls << ";";
    oss << "level=" << state.level << ";";
    oss << "score=" << state.score << ";";

    // Serialize input values
    oss << "inputLeftUp=" << state.inputLeftUp << ";";
    oss << "inputLeftDown=" << state.inputLeftDown << ";";
    oss << "inputRightUp=" << state.inputRightUp << ";";
    oss << "inputRightDown=" << state.inputRightDown << ";";

    // Serialize limit flags
    oss << "limitAngle=" << state.limitAngle << ";";
    oss << "limitLeftUp=" << state.limitLeftUp << ";";
    oss << "limitLeftDown=" << state.limitLeftDown << ";";
    oss << "limitRightUp=" << state.limitRightUp << ";";
    oss << "limitRightDown=" << state.limitRightDown << ";";

    // Serialize ball states
    oss << "ballOnTarget=" << state.ballOnTarget << ";";
    oss << "ballReady=" << state.ballReady << ";";

    // Serialize configuration
    oss << "speedDown=" << state.speedDown << ";";
    oss << "speedUp=" << state.speedUp << ";";

    // Serialize motor outputs
    oss << "motorLeftUp=" << state.motorLeftUp << ";";
    oss << "motorLeftDown=" << state.motorLeftDown << ";";
    oss << "motorRightUp=" << state.motorRightUp << ";";
    oss << "motorRightDown=" << state.motorRightDown << ";";

    return oss.str();
}
