#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    std::cout << path << std::endl;

    auto pin0 = due::pin_out(due::pins::d52);
    auto pin1 = due::pin_out(due::pins::d50);
    auto pin2 = due::pin_out(due::pins::d48);
    auto pin3 = due::pin_out(due::pins::d46);
    auto pin4 = due::pin_out(due::pins::d44);
    auto pin5 = due::pin_out(due::pins::d42);
    auto pin6 = due::pin_out(due::pins::d40);
    auto pin7 = due::pin_out(due::pins::d38);

    // auto set0 = due::all_from_pin_out_t(pin0, pin1, pin4, pin5);
    // auto set1 = due::all_from_pin_out_t(pin2, pin3, pin6, pin7);

    auto port0 = due::port_out_from_pins_t(pin0, pin1, pin4, pin5);
    auto port1 = due::port_out_from_pins_t(pin2, pin3, pin6, pin7);
    auto portSet0 = due::all_from_port_out_t(port0);
    auto portSet1 = due::all_from_port_out_t(port1);

    due_remote::waitForStartSignal();
    
    for(;;){
        portSet0.write(9999'9999);
        portSet0.flush();
        portSet0.write(0);
        portSet0.flush();

        portSet1.write(9999'9999);
        portSet1.flush();
        portSet1.write(0);
        portSet1.flush();
    }
}