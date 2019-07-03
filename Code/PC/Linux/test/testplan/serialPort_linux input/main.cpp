#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    due::pin_out pin0 = due::pin_out(due::pins::d52);
    due::pin_out pin1 = due::pin_out(due::pins::d50);

    std::cout << "SerialPort_linux initialized correctly." << std::endl;

    due_remote::waitForStartSignal();
    
    for(;;){
        if(pin1.read()){
            std::cout << "serialPort readBool: 1" << std::endl;
        }
        else{
            std::cout << "serialPort readBool: 0" << std::endl;
        }

        std::cout << "serialPort readInt: " << serialPort.readInt() << std::endl;
        hwlib::wait_ms(28);

        std::cout << "serialPort readChar: " << serialPort.readChar() << std::endl;
        
    }
}