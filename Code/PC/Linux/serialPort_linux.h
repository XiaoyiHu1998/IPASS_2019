#ifndef SERIALPORT_LINUX_H
#define SERIALPORT_LINUX_H

//C library headers
#include "stdio.h"
#include "string.h"

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
    serialPort_linux(string & path);
    ~serialPort_linux();

    //writes size amount of chars in message to serial port,
    //returns amount sent, or < 0 if error occured
    int write(const void *message, const size_t size);

    char* read(const size_t toRead);
};

#endif //SERIALPORT LINUX_H