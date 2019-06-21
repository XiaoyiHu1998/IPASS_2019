#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

int main(){
    auto pin = due_remote::pin_out(due_remote::pins::d13);

    for(;;){
        pin.write(1);
        pin.flush();
        hwlib::wait_ms(100);
        pin.write(0);
        pin.flush();
        hwlib::wait_ms(100);
    }
}