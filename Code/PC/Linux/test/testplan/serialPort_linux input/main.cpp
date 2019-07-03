#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"

namespace due = due_remote;

int main(){
    due::pin_in pin = due::pin_in(due::pins::d52);

    std::cout << "SerialPort_linux initialized correctly." << std::endl;

    due_remote::waitForStartSignal();
    
    for(;;){
        if(pin.read()){
            std::cout << "serialPort readBool: 1" << std::endl;
        }
        else{
            std::cout << "serialPort readBool: 0" << std::endl;
        }
        hwlib::wait_ms(28);

        std::cout << "serialPort readInt: " << serialPort.readInt() << std::endl;
        hwlib::wait_ms(28);

        std::cout << "serialPort readChar: " << serialPort.readChar() << std::endl;
        hwlib::wait_ms(28);
    }
}