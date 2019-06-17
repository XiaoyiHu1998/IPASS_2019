#include "serialPort.h"

serialPort::serialPort(const char[4] & comPort):
                                        comPort(comPort),
                                        hComm(NULL),
                                        open(false),
                                        status(),
                                        errors()
                                        {}

//open serial port connection
void serialPort::open(const int nBaudRate){
    //connect through given port with CreateFile
    hComm = CreateFile("\\\\.\\" + comPort,
                        GENERIC_READ | GENERIC WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL);

    //connection success check
    if(hComm == INVALID_HANDLE_VALUE){
        //error
        std::cout << "ERROR: serial port -> " << GetLastError() << endl;
    }
    else{
        //success
        std::cout << "Serial port open" << endl;
        open = true;

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
            dcbSerialParams.parity = NOPARITY;
            //set DTR control to reset arduino if connection is made.
            dcbSerialParams.fDtrControl = DTR_CONTROL_DISABLE;

            //set parameters and check for their proper application
            if(!SetCommState(hComm, &dcbSerialParams)){
                std::cout << "Aler: could not set serial port parameters" << endl;
            }
            else{
                //connected if everything is fine
                this->open = true;
                //flush buffer
                PurgeComm(this->hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
                //wait for arduino to reset for 2 seconds
                Sleep(2000);
            }
        }
    }
}

serialPort::~serialPort(){
    if(open){
        open  = false;
        CloseHandle(hComm);
    }
}

void serialPort::close(){
    if(open){
        CloseHandle(hComm);
        open = false;
    }
}

void serialPort:changePort(const char[4] & newPort){
    if(!open){
        comPort = newPort;
        std::cout << "portChanged to " + comPort << endl;
    }
}

int serialPort::read(const char & *buffer, const unsigned int CharCount){
    //Number of bytes to read
    DWORD bytesRead;
    //amount of bytes asked to read
    unsigned int toRead;

    //get status info on port
    ClearCommError(hcomm. &this->errors, &this->status);

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

bool serialPort::write(const char & *buffer, unsigned int charCount){
    DWORD bytesSend;

    //try to write buffer to port
    if(WriteFile(hComm, &this->errors, &this->status)){
        return true;
    }
    else{
        return false;
    }
}

bool serialPort::isOpen(){
    //return connection status
    return open;
}