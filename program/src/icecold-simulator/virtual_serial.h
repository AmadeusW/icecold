#ifndef VIRTUAL_SERIAL_H
#define VIRTUAL_SERIAL_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

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

        // Set non-blocking mode for master FD
        int flags = fcntl(masterFd, F_GETFL, 0);
        if (flags == -1) {
            close(masterFd);
            throw std::runtime_error("Failed to get file descriptor flags");
        }

        if (fcntl(masterFd, F_SETFL, flags | O_NONBLOCK) == -1) {
            close(masterFd);
            throw std::runtime_error("Failed to set non-blocking mode");
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

#endif
