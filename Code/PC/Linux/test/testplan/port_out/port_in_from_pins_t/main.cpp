#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    auto pin0 = due::pin_in(due::pins::d52);
    auto pin1 = due::pin_in(due::pins::d50);
    auto pin2 = due::pin_in(due::pins::d48);
    auto pin3 = due::pin_in(due::pins::d46);
    auto pin4 = due::pin_in(due::pins::d44);
    auto pin5 = due::pin_in(due::pins::d42);
    auto pin6 = due::pin_in(due::pins::d40);
    auto pin7 = due::pin_in(due::pins::d38);

    auto port0 = due::port_in_from_pins_t(pin0, pin1, pin4, pin5);
    auto port1 = due::port_in_from_pins_t(pin2, pin3, pin6, pin7);

    due_remote::waitForStartSignal();

    uint_fast16_t row1;
    uint_fast16_t row2;
    
    for(;;){
        port0.refresh();
        row1 = port0.read();
        std::cout << row1 << std::endl;

        port1.refresh();
        row2 = port1.read();
        std::cout << row2<< std::endl;
    }
}