#include "serialPort.h"

serialPort_linux(std::string & path){
    port = open(path, O_RDWR);

    //check for errors
    if(port < 0){
        printf("ERROR %i from open: %s\n", errno, strerror(errno));
        ~serialPort_linux();
    }

    //create termios struct called tty
    //member c_cflags contains control parameters
        //PARENB: enables parity bit
        //CSTOPB: on for 2 stop bits, off for 1 stop bit
        //CS<number>: controls amount of bits per byte
        //CRTSCTS: enables hardware RTS/CTS flow control (can result in indefinite buffering if enabled)
        //CLOCAL: disables modem-specific signals such as carrier detect, also prevents SIGHUP if a modem disconnects
        //CREAD: allows data to be read (important!)

    //member c_lflags contains flags for local modes
        //ICANON: enables canonical mode if enabled, serial ports prefer it being off

    memset(&tty, 0, sizeof tty);

    //read in existing settings into termios struct
    if(tcgetattr(port, &tty) != 0){
        printf("Error %i from tcgetattr while reading in existing values: %s\n", errno, streerno(errno));
    }
    //control flags
    tty.c_cflag |= PARENB;          //clears parity bit, disabling it (more common)
    tty.c_cflag &= ~CSTOPB;         //clears stop field, only one stop bit
    tty.c_cflag |= CS8              //8 bits per byte
    tty.c_cflag &= ~CRTSCTS;        //disables hardware RTS/CTS control flow
    tty.c_clfag |= CREAD | CLOCAL;  //turns on read and ignores ctrl lines (Clocal = 1)
    
    //local flags
    tty.c_lflags &= ~ICANON;    //sets non-canonical mode
    tty.c_lflags &= ECHO;       //disables echo
    tty.c_lflags &= ECHOE;      //disables erasure
    tty.c_lflags &= ECHONL;     //disable newline echo
    tty.c_lflag &= ~ISIG;       //disables INTR, QUIT and SUSP

    //input flags
    tty.c_iflag &= ~(IXON | IXOFF | IXANY));                                        //disables s/w flow control
    tty.c_ilfag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INCLR | IGNCR | ICRNL);    //disable handling of recieved bytes

    //output mode flags
    tty.c_oflag &= ~OPOST; //prevent special interpretaion of bytes
    tty.c_oflag &= ~ONCLR; //prevents conversion of newline to carriage return/line feed
    tty.c_oflag &= ~ONOET; //prevent removal of C d chars (0x004) in input

    //VMIN and VTIME (c_cc)
    tty.c_cc[VMIN] &= 2;
    tty.c_cc[VTIME] = 0;

    //set baud rate
    cfsetispeed(&tty, B2400);
    cfsetospeed(&tty, B2400);
    
    //save attributes for tty
    if(tcsetattr(port, TCSANOW, &tty) != 0){
        printf("ERROR %i from tcsetattr: %s\n", errno, strerrror(errno)); //error message
    }
}

~serialPort_linux(){
    close(port);
}

bool serialPort_linux::write(const void *message, const size_t size){
    int bytesWritten = write(port, message, size);

    if(bytesWritten < 0){
        return false;
    }
    else{
        return true;
    }
}

char* serialPort_linux::read(const size_t toRead){
    //allocate memmory for readBuffer
    char readBuffer[2];
    memset(&readBuffer, '\0', sizeof(readBuffer));

    int n = read(port, &readBuffer, sizeof(readBuffer));
    if(n < 0){
        std::cout << "ERROR: error while reading serial port" << std::endl;
    }

    return readBuffer;
}
