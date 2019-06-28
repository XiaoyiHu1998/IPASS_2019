#include "serialPort_linux.hpp"

serialPort_linux::serialPort_linux(char* path){
    port = open(path, O_RDWR);

    //check for errors
    if(port < 0){
        printf("ERROR %i from open: %s\n", errno, strerror(errno));
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
        printf("ERROR %i from tcgetattr while reading in existing values: %s\n", errno, strerror(errno));
    }
    //control flags
    tty.c_cflag |= PARENB;          //clears parity bit, disabling it (more common)
    tty.c_cflag &= ~CSTOPB;         //clears stop field, only one stop bit
    tty.c_cflag |= CS8;             //8 bits per byte
    tty.c_cflag &= ~CRTSCTS;        //disables hardware RTS/CTS control flow
    tty.c_cflag |= CREAD | CLOCAL;  //turns on read and ignores ctrl lines (Clocal = 1)
    tty.c_cflag &= ~HUPCL;       //Turn off hangup to prevent reset on read wite switch
    
    //local flags
    tty.c_lflag &= ~ICANON;    //sets non-canonical mode
    tty.c_lflag &= ECHO;       //disables echo
    tty.c_lflag &= ECHOE;      //disables erasure
    tty.c_lflag &= ECHONL;     //disable newline echo
    tty.c_lflag &= ~ISIG;       //disables INTR, QUIT and SUSP

    //input flags
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                        //disables s/w flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);   //disable handling of recieved bytes

    //output mode flags
    tty.c_oflag &= ~OPOST; //prevent special interpretaion of bytes
    tty.c_oflag &= ~ONLCR; //prevents conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~ONOET; //prevent removal of C d chars (0x004) in input

    //VMIN and VTIME (c_cc)
    tty.c_cc[VMIN] &= 2;
    tty.c_cc[VTIME] = 0;

    //set baud rate
    cfsetispeed(&tty, B2400);
    cfsetospeed(&tty, B2400);
    
    //save attributes for tty
    if(tcsetattr(port, TCSANOW, &tty) != 0){
        printf("ERROR %i from tcsetattr: %s\n", errno, strerror(errno)); //error message
    }
}

serialPort_linux::~serialPort_linux(){
    close(port);
}

bool serialPort_linux::writeChar(const char message, const size_t size){
    int bytesWritten = write(port, &message, size);

    if(bytesWritten < 0){
        return false;
    }
    else{
        return true;
    }
}

bool serialPort_linux::writeInt(const uint8_t message, const size_t size){
    int bytesWritten = write(port, &message, size);

    if(bytesWritten < 0){
        return false;
    }
    else{
        return true;
    }
}

bool serialPort_linux::readBool(){
    char buffer;
    int amountRead = read(port, &buffer, sizeof(buffer));
    std::cout << "Read: " << amountRead << " Value: " << buffer << std::endl;
    if(amountRead < 0){
        std::cout << "ERROR: error while reading serial port" << std::endl;
    }

    switch(buffer){
        case '1':
            return true;
            break;
        case '0':
            return false;
            break;
        case 'e':
            std::cout << "Error: serial port did not return expected bool values, 'e' recieved";
            return false;
            break;
        default:
            std::cout << "Error: serial port did not return expected bool values, unkown value recieved";
            return false;
            break;
    }
}
