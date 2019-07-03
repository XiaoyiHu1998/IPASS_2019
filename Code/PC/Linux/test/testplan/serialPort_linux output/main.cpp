#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    due::pin_out pin0 = due::pin_out(due::pins::d52);

    std::cout << "SerialPort_linux initialized correctly." << std::endl;

    due_remote::waitForStartSignal();
    
    for(;;){
        pin.write(1);
        pin.flush();

        hwlib::wait_ms(500);

        pin.write(0);
        pin.flush();
    }
}