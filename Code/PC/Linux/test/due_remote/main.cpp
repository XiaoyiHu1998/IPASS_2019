#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"


int main(){
    std::cout << path << std::endl;
    auto pin = due_remote::pin_out(due_remote::pins::d52);
    auto pin2 = due_remote::pin_out(due_remote::pins::d50);
    auto pin3 = due_remote::pin_in(due_remote::pins::d48);

    for(;;){
        pin.write(1);
        // pin.flush();
        std::cout << "on" << std::endl;
        hwlib::wait_ms(100);

        pin3.refresh();
        hwlib::wait_ms(100);
        if(pin3.read()){
            hwlib::wait_ms(100);
            pin2.write(1);
            // pin2.flush();
            std::cout << "!on" << std::endl;
        }
        else{
            hwlib::wait_ms(100);
            pin2.write(0);
            // pin2.flush();
            std::cout << "!off" << std::endl;
        }
        hwlib::wait_ms(100);

        pin.write(0);
        // pin.flush();
        std::cout << "off" << std::endl << std::endl;
        hwlib::wait_ms(100);

    }
}