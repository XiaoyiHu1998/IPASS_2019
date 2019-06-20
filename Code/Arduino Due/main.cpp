#include "hwlib.hpp"
namespace target = hwlib::target;

void blink(target::pin_out pin, int time){
    pin.write(1);
    pin.flush();
    hwlib::wait_us(time);
    pin.write(0);
    pin.flush();
    hwlib::wait_us(time);
}

int main(){
    hwlib::wait_ms(100);
    char input;
    auto pin = target::pin_out(target::pins::d13);
    for(int i = 0; i < 5; i++){
                pin.write(1);
                pin.flush();
                hwlib::wait_us(5);
                pin.write(0);
                pin.flush();
                hwlib::wait_us(5);
    }

    while(1){
        hwlib::cin >> input;
        if(input == 'a'){
            blink(pin, 5);
        }
        hwlib::wait_us(1);
    }
    
}