#include "../serialPort_linux.h"
#include "string.h"

int main(){
    char path[13] = "/dev/ttyUSB0";
    char character = 'c';
    // std::cout << "Please enter the path of of your serial port: ";
    // std::cin >> path;
    serialPort_linux port(path);

    while(1){
        std::cout << port.writeData("a", 1);
        sleep(2);
    }
}