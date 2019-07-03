#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    auto pin0 = due::pin_in_out_dummy(due::pins::d52);

    due_remote::waitForStartSignal();
    
    for(;;){
        pin0.write(1);
        pin0.flush();
        hwlib::wait_ms(500);
        pin0.write(0);
        pin0.flush();
    }
}