#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    auto pin0 = due::pin_adc_dummy();

    due_remote::waitForStartSignal();
    
    for(;;){
        pin0.refresh();
        hwlib::wait_ms(28);
        std::cout << "pin_adc reading value: " << pin0.read() << std::endl;
        hwlib::wait_ms(28);
    }
}