#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::string;

class serialPort{
private:
    char comPort[4];
    Handle hComm;
    bool open;
    COMSTAT status;
    DWORD errors;
public:
    serialPort(const char[4] & comPort);
    void open(const int nBaudRate);
    void close();
    void changePort(const char[4] & newPort);
    int read(const char & *buffer, const unsigned int CharCount);
    bool write(const char & *buffer, unsigned int charCount);
    bool isOpen();
};