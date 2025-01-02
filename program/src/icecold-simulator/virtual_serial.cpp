#include <cstring>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include "icecold-simulator.h"

class VirtualSerialPort {
private:
    int masterFd;
    int slaveFd;
    char slavePath[256];

public:
    VirtualSerialPort() : masterFd(-1), slaveFd(-1) {
        // Create a pseudo-terminal
        masterFd = posix_openpt(O_RDWR);
        if (masterFd == -1) {
            throw std::runtime_error("Failed to open pseudo-terminal");
        }

        // Grant slave access
        if (grantpt(masterFd) == -1) {
            close(masterFd);
            throw std::runtime_error("Failed to grant slave access");
        }

        // Unlock slave
        if (unlockpt(masterFd) == -1) {
            close(masterFd);
            throw std::runtime_error("Failed to unlock slave");
        }

        // Get slave path
        char* pts_name = ptsname(masterFd);
        if (pts_name == nullptr) {
            close(masterFd);
            throw std::runtime_error("Failed to get slave path");
        }
        strncpy(slavePath, pts_name, sizeof(slavePath));

        // Open slave file descriptor
        slaveFd = open(slavePath, O_RDWR);
        if (slaveFd == -1) {
            close(masterFd);
            throw std::runtime_error("Failed to open slave descriptor");
        }

        // Configure terminal settings
        struct termios termSettings;
        tcgetattr(slaveFd, &termSettings);
        
        // Set standard baud rate and configuration
        cfsetispeed(&termSettings, B115200);
        cfsetospeed(&termSettings, B115200);
        
        // Raw mode configuration
        termSettings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
        termSettings.c_oflag &= ~OPOST;
        termSettings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        termSettings.c_cflag &= ~(CSIZE | PARENB);
        termSettings.c_cflag |= CS8;

        tcsetattr(slaveFd, TCSANOW, &termSettings);
    }

    ~VirtualSerialPort() {
        if (masterFd != -1) close(masterFd);
        if (slaveFd != -1) close(slaveFd);
    }

    // Get the path to the virtual serial port
    std::string getPortPath() const {
        return std::string(slavePath);
    }

    // Write data to the virtual port
    ssize_t write(const std::string& data) {
        return ::write(masterFd, data.c_str(), data.length());
    }

    // Read data from the virtual port
    std::string read(size_t maxLength = 1024) {
        char buffer[maxLength];
        ssize_t bytesRead = ::read(masterFd, buffer, maxLength);
        
        if (bytesRead > 0) {
            return std::string(buffer, bytesRead);
        }
        return "";
    }
};

int main() {
    try {
        // Create virtual serial port
        VirtualSerialPort virtualPort;
        
        std::cout << "Virtual Serial Port Created at: " << virtualPort.getPortPath() << std::endl;
        setup();

        // Simulate device communication
        std::thread simulatorThread([&virtualPort]() {
            while (true) {
                // Example: Send periodic status messages
                std::string statusMsg = "DEVICE_STATUS:OPERATIONAL\n";
                virtualPort.write(statusMsg);
                loop();
                
                // Wait for 5 seconds
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        });

        // Optional: Read loop to process incoming commands
        std::thread readerThread([&virtualPort]() {
            while (true) {
                std::string receivedData = virtualPort.read();
                if (!receivedData.empty()) {
                    std::cout << "Received: " << receivedData;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });

        // Keep main thread running
        simulatorThread.join();
        readerThread.join();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
