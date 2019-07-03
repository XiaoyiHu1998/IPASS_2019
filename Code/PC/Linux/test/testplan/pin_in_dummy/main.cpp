#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    auto pin0 = due::pin_in_dummy(due::pins::d52);

    due_remote::waitForStartSignal();
    
    for(;;){
        pin0.refresh();
        std::cout << "Value read on pin 52" << pin0.read() << std::endl;
        hwlib::wait_ms(500);
    }
}