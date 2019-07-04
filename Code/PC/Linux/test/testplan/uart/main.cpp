#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    char output;

    due_remote::waitForStartSignal();
    
    for(;;){
        std::cout << "give a single character" << std::endl;
        output = due::uart_getc();
        std::cout << "previous input: " << output << std::endl;
    }
}