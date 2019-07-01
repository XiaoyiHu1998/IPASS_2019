#include <iostream>
#include "/home/xiaoyi/hwlib/library/hwlib.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/hwlib/hwlib-arduino-due-remote.hpp"


int main(){
    std::cout << path << std::endl;
    std::cout << "waiting for arduino" << std::endl;

    auto pin = due_remote::pin_out(due_remote::pins::d52);
    auto pin2 = due_remote::pin_out(due_remote::pins::d50);
    auto pin3 = due_remote::pin_in(due_remote::pins::d48);
    auto pin4 = due_remote::pin_adc(due_remote::adc_pins::ad8);

    due_remote::waitForArduino();

    for(;;){
        pin.write(1);
        // pin.flush();
        std::cout << "on" << std::endl;
        // hwlib::wait_ms(80);

        pin3.refresh();
        // hwlib::wait_ms(80);
        if(pin3.read()){
            // hwlib::wait_ms(80);
            pin2.write(1);
            // pin2.flush();
            std::cout << "!on" << std::endl;
        }
        else{
            // hwlib::wait_ms(80);
            pin2.write(0);
            // pin2.flush();
            std::cout << "!off" << std::endl;
        }
        // hwlib::wait_ms(80);

        // pin4.refresh();
        // hwlib::wait_ms(80);
        // std::cout << "ADC: "<< pin4.read() << std::endl;
        // hwlib::wait_ms(80);

        pin.write(0);
        // pin.flush();
        std::cout << "off" << std::endl << std::endl;
        // hwlib::wait_ms(80);

        

    }
}