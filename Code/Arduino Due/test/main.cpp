// testfile

#include "hwlib.hpp"
namespace target = hwlib::target;

void blink(target::pin_out pin, int time){
    pin.write(1);
    pin.flush();
    hwlib::wait_ms(time);
    pin.write(0);
    pin.flush();
    hwlib::wait_ms(time);
}

int main(){
    hwlib::wait_ms(100);
    char input;
    auto pin = target::pin_out(target::pins::d13);
    for(int i = 0; i < 5; i++){
                pin.write(1);
                pin.flush();
                hwlib::wait_ms(500);
                pin.write(0);
                pin.flush();
                hwlib::wait_ms(100);
            }

    while(1){
        hwlib::cin >> input;
        if(input == 'a'){
            for (int x = 1; x < 6; x++){
                blink(pin, x * 100);
            }
        }
        hwlib::wait_ms(500);
    }
    
}