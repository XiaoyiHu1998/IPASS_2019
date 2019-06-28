#ifndef SERIALPORT_LINUX_HPP
#define SERIALPORT_LINUX_HPP

//C library headers
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <array>

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
    bool writeChar(const char message, const size_t size);

    //send uint8_t over serial port
    bool writeInt(const uint8_t message, const size_t size);

    //writes char array with size N over serial port
    template<unsigned int N> 
    bool writeArray(const std::array<char, N> & message){
        unsigned int bytesWritten = 0;
        while(bytesWritten < N){
            int bytesSent = write(port, message.data() + bytesWritten, N - bytesWritten);
            if(bytesSent < 0){
                std::cout << "ERROR: bytes could not be sent." << std::endl;
                return false;
            }
            else{
                bytesWritten += static_cast<unsigned int>(bytesSent);
                return true;
            }
        }
    }

    bool readBool();

    // //reads N amount of bools from serial port.
    // template<unsigned int N> 
    // bool writeArray(const std::array<char, N> & message){
    //     unsigned int bytesWritten = 0;
    //     while(bytesWritten < N){
    //         int bytesSent = write(port, message.data() + bytesWritten, N - bytesWritten);
    //         if(bytesSent < 0){
    //             std::cout << "ERROR: bytes could not be sent." << std::endl;
    //             return false;
    //         }
    //         else{
    //             bytesWritten += static_cast<unsigned int>(bytesSent);
    //             return true;
    //         }
    //     }
    // }

    // void readData(char* readBuffer, const size_t toRead);
};

#endif //SERIALPORT LINUX_H