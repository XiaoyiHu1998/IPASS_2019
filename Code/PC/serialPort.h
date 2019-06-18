#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class serialPort{
private:
    char comPort[4];
    HANDLE hComm;
    bool open;
    COMSTAT status;
    DWORD errors;
public:
    serialPort(const char (&comPort)[4]);
    ~serialPort();
    void open(const int nBaudRate);
    void close();
    void changePort(const char (&newPort)[4]);
    int read(const char *buffer, const unsigned int CharCount);
    bool write(const char *buffer, unsigned int charCount);
    bool isOpen();
};

#endif //SERIALPORT_H