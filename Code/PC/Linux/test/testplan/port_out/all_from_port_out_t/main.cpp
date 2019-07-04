#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    auto pin0 = due::pin_out(due::pins::d52);
    auto pin1 = due::pin_out(due::pins::d50);
    auto pin2 = due::pin_out(due::pins::d48);
    auto pin3 = due::pin_out(due::pins::d46);
    auto pin4 = due::pin_out(due::pins::d44);
    auto pin5 = due::pin_out(due::pins::d42);
    auto pin6 = due::pin_out(due::pins::d40);
    auto pin7 = due::pin_out(due::pins::d38);

    auto port0 = due::port_out_from_pins_t(pin0, pin1, pin4, pin5);
    auto port1 = due::port_out_from_pins_t(pin2, pin3, pin6, pin7);
    auto portSet0 = due::all_from_port_out_t(port0);
    auto portSet1 = due::all_from_port_out_t(port1);

    due_remote::waitForStartSignal();
    
    for(;;){
        port0.write(1);
        port0.flush();
        hwlib::wait_ms(200);
        port0.write(0);
        port0.flush();
        hwlib::wait_ms(200);

        port1.write(1);
        port1.flush();
        hwlib::wait_ms(200);
        port1.write(0);
        port1.flush();
        hwlib::wait_ms(200);
    }
}