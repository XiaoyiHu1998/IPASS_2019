#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    auto pin0 = due::pin_oc_dummy();
    auto pin1 = due::pin_oc_dummy();

    due_remote::waitForStartSignal();
    
    for(;;){
        if(pin0.read()){
            hwlib::wait_ms(28);
            pin1.write(1);
            hwlib::wait_ms(28);
            pin1.flush();
        }
        else{
            hwlib::wait_ms(28);
            pin1.write(0);
            hwlib::wait_ms(28);
            pin1.flush();
        }
        hwlib::wait_ms(28);

        pin1.write(1);
        pin1.flush();
        pin1.write(0);
        pin1.flush();
    }
}