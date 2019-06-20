#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class serialPort_windows{
private:
    char *portName;
    HANDLE hComm;
    bool connected;
    COMSTAT status;
    DWORD errors;
public:
    serialPort(char *portName);
    ~serialPort();
    void open(const int nBaudRate);
    void close();
    int read(char *buffer, const unsigned int CharCount);
    bool write(const char *buffer, unsigned int charCount);
    bool isConnected();
};

#endif //SERIALPORT_H
