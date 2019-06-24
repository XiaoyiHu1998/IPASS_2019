#ifndef SERIALPORT_LINUX_H
#define SERIALPORT_LINUX_H

//C library headers
#include "stdio.h"
#include "string.h"
#include <iostream>

//Linux headers
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

class serialPort_linux{
private:
   int port;
   struct termios tty;
public:
    serialPort_linux(char* path);
    ~serialPort_linux();

    //send char over serial port
    bool serialPort_linux::writeChar(const char message, const size_t size);

    //send uint8_t over serial port
    bool serialPort_linux::writeInt(const uint8_t message, const size_t size);

    //writes char array with size N over serial port
    template<unsigned int N> bool writeArray(const std::array<char, N> & message);

    void readData(char* & readBuffer, const size_t toRead);
};

#endif //SERIALPORT LINUX_H