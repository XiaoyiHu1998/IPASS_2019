#include "serialPort.h_windows"
#include <iostream>

using std::endl;
using std::cout;
using std::cin;

serialPort__windows::serialPort_windows(char *portName):
                                        portName(portName),
                                        hComm(NULL),
                                        connected(false),
                                        status(),
                                        errors()
                                        {}

serialPort_windows::~serialPort_windows(){
    if(connected){
        connected  = false;
        CloseHandle(hComm);
    }
}

//open serial port connection
void serialPort_windows::open(const int nBaudRate){
    //connect through given port with CreateFile
    hComm = CreateFile( portName,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL);

    //connection success check
    if(this->hComm == INVALID_HANDLE_VALUE){
        //error
        std::cout << "ERROR: serial port INVALID_HANDLE_VALUE -> " << GetLastError() << endl;
    }
    else{
        //success
        std::cout << "Serial port open" << endl;
        connected = true;

        //try to set comm parameters
        DCB dcbSerialParams = {0};

        //try to get current
        if(!GetCommState(this->hComm, & dcbSerialParams)){
            //error if not possible
            std::cout << "Failed to get current serial parameters" << endl;
        }
        else{
            //define serial parameters for arduino
            dcbSerialParams.BaudRate = nBaudRate;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;
            //set DTR control to reset arduino if connection is made.
            dcbSerialParams.fDtrControl = DTR_CONTROL_DISABLE;

            //set parameters and check for their proper application
            if(!SetCommState(hComm, &dcbSerialParams)){
                std::cout << "Aler: could not set serial port parameters" << endl;
            }
            else{
                //connected if everything is fine
                connected = true;
                //flush buffer
                PurgeComm(this->hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
                //wait for arduino to reset for 2 seconds
                Sleep(2000);
            }
        }
    }
}

void serialPort_windows::close(){
    if(connected){
        CloseHandle(hComm);
        connected = false;
    }
}

int serialPort_windows::read(char *buffer, const unsigned int charCount){
    //Number of bytes to read
    DWORD bytesRead;
    //amount of bytes asked to read
    unsigned int toRead;

    //get status info on port
    ClearCommError(hComm, &this->errors, &this->status);

    //check for things available to read
    if(status.cbInQue > 0){
        //check if enough data to read the amount wanted, if not read whats available for now
        if(status.cbInQue > charCount){
            toRead = charCount;
        }
        else{
            toRead = status.cbInQue;
        }

        //try reading required amount fo characters and return amount of read bytes
        if(ReadFile(hComm, buffer, toRead, &bytesRead, NULL)){
            return bytesRead;
        }
    }

    //return 0 if nothing read or error detected
    return 0;
}

bool serialPort::write(const char *buffer, unsigned int charCount){
    DWORD bytesSent;

    //try to write buffer to port
    if(WriteFile(hComm, (void*)buffer, charCount, &bytesSent, 0)){
        return true;
    }
    else{
        //get Comm error
        ClearCommError(hComm, &this->errors, &this->status);
        return false;
    }
}

bool serialPort_windows::isConnected(){
    //return connection status
    return connected;
}