#include "hwlib.hpp"
namespace target = hwlib::target;

int main(){
    char input;
    auto pin = target::pin_out(target::pins::d13);

    while(1){
        hwlib::cin >> input;
        if(input == 'a'){
            for(int i = 0; i < 5; i++){
                pin.write(1);
                pin.flush();
                hwlib::wait_ms(200);
                pin.write(0);
                pin.flush();
                hwlib::wait_ms(200);
            }
            
        }
        hwlib::wait_ms(100);
    }
    
}