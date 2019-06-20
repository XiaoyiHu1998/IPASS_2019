#include "../serialPort.h"
#include <iostream>
#include "stdlib.h"

char com[] = "\\\\.\\COM4";
serialPort port(com);

int main(){
    char message;
    char buffer[1];
    port.open(9600);

    if(port.isConnected()){
        for(;;){
            std::cout << "enter leter a:" << std::endl;
            std::cin >> message;
            std::cout << "success: "<< port.write(&message, 1) << std::endl;
            std::cout << "Read bytes: " << port.read(buffer, 1) << " Value: " << buffer << std::endl;
            Sleep(3);
        }
    }
    
}