#include "../serialPort_linux.h"
#include "string.h"

int main(){
    char path[13] = "/dev/ttyUSB0";
    std::cout << path << std::endl;
    serialPort_linux port(path);

    while(1){
        // std::cout << "Enter a to blink: ";
        // std::cin >> character;
        for(;;){
            usleep(1000);
            std::cout << port.writeChar('a', 1);
        }
    }
}