#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"


int main(){
    std::cout << path << std::endl;
    auto pin = due_remote::pin_out(due_remote::pins::d53);
    auto pin2 = due_remote::pin_out(due_remote::pins::d8);

    for(;;){
        pin.write(1);
        // pin.flush();
        std::cout << "on" << std::endl;
        hwlib::wait_ms(1000);
        pin.write(0);
        // pin.flush();
        std::cout << "off" << std::endl;
        hwlib::wait_ms(1000);

        pin2.write(1);
        // pin.flush();
        std::cout << "on" << std::endl;
        hwlib::wait_ms(1000);
        pin2.write(0);
        // pin.flush();
        std::cout << "off" << std::endl;
        hwlib::wait_ms(1000);
    }
}