#include "hwlib.hpp"
#include "duePins.h"

namespace target = hwlib::target;

target::pin_in_out pins[54] = {
                                    target::pin_in_out(target::pins::d0),
                                    target::pin_in_out(target::pins::d1),
                                    target::pin_in_out(target::pins::d2),
                                    target::pin_in_out(target::pins::d3),
                                    target::pin_in_out(target::pins::d4),
                                    
                                    target::pin_in_out(target::pins::d5),
                                    target::pin_in_out(target::pins::d6),
                                    target::pin_in_out(target::pins::d7),
                                    target::pin_in_out(target::pins::d8),
                                    target::pin_in_out(target::pins::d9),
                                    
                                    target::pin_in_out(target::pins::d10),
                                    target::pin_in_out(target::pins::d11),
                                    target::pin_in_out(target::pins::d12),
                                    target::pin_in_out(target::pins::d13),
                                    target::pin_in_out(target::pins::d14),
                                    
                                    target::pin_in_out(target::pins::d15),
                                    target::pin_in_out(target::pins::d16),
                                    target::pin_in_out(target::pins::d17),
                                    target::pin_in_out(target::pins::d18),
                                    target::pin_in_out(target::pins::d19),
                                    
                                    target::pin_in_out(target::pins::d20),
                                    target::pin_in_out(target::pins::d21),
                                    target::pin_in_out(target::pins::d22),
                                    target::pin_in_out(target::pins::d23),
                                    target::pin_in_out(target::pins::d24),
                                    
                                    target::pin_in_out(target::pins::d25),
                                    target::pin_in_out(target::pins::d26),
                                    target::pin_in_out(target::pins::d27),
                                    target::pin_in_out(target::pins::d28),
                                    target::pin_in_out(target::pins::d29),
                                    
                                    target::pin_in_out(target::pins::d30),
                                    target::pin_in_out(target::pins::d31),
                                    target::pin_in_out(target::pins::d32),
                                    target::pin_in_out(target::pins::d33),
                                    target::pin_in_out(target::pins::d34),
                                    
                                    target::pin_in_out(target::pins::d35),
                                    target::pin_in_out(target::pins::d36),
                                    target::pin_in_out(target::pins::d37),
                                    target::pin_in_out(target::pins::d38),
                                    target::pin_in_out(target::pins::d39),
                                    
                                    target::pin_in_out(target::pins::d40),
                                    target::pin_in_out(target::pins::d41),
                                    target::pin_in_out(target::pins::d42),
                                    target::pin_in_out(target::pins::d43),
                                    target::pin_in_out(target::pins::d44),
                                    
                                    target::pin_in_out(target::pins::d45),
                                    target::pin_in_out(target::pins::d46),
                                    target::pin_in_out(target::pins::d47),
                                    target::pin_in_out(target::pins::d48),
                                    target::pin_in_out(target::pins::d49),
                                    
                                    target::pin_in_out(target::pins::d50),
                                    target::pin_in_out(target::pins::d51),
                                    target::pin_in_out(target::pins::d52),
                                    target::pin_in_out(target::pins::d53)
                                };

duePins duePins(pins);

char getNextParamter(){
    char parameter;
    hwlib::cin >> parameter;

    return parameter;
}

int main(){
    while(1){
        char classChar;
        char function;
        hwlib::cin >> classChar;
        hwlib::cin >> function;

        switch(classChar){
            //ad_pin_type_info
            case '1':
            //d2_36kHz
            case '2':
            //pin_adc
            case '3':
            //pin_in
            case '4':
                // switch(function){
                //     //constructor call, enable pin as input
                //     case 'c':
                //         setPinIO(1);
                    
                //     //pin_in.pullup_disable()
                //     case '1':
                        

                //     //pin_in.pullup_enable()
                //     case '2':

                //     //pin_in.read()
                //     case '3':

                //     //pin_in.refresh()
                //     case '4':

                // }

            //pin_in_out
            case '5':
                int pinNumber = 0;

                switch(function){
                    //setOutput()
                    case '1':
                        for(unsigned int i = 0; i < 6; i++){
                            char value = getNextParamter();
                            
                            pinNumber += int (value);
                        }

                        duePins.setOutput(pinNumber);

                    //setInput()
                    case '2':
                        for(unsigned int i = 0; i < 6; i++){
                            char value = getNextParamter();
                            
                            pinNumber += int (value);
                        }

                        duePins.setInput(pinNumber);

                    //write()
                    case '3':
                        for(unsigned int i = 0; i < 6; i++){
                            char value = getNextParamter();
                            
                            pinNumber += int (value);
                        }

                        if(getNextParamter() == '1'){
                            duePins.write(pinNumber, 1);
                        }
                        else{
                            duePins.write(pinNumber, 0);
                        }

                    //read()
                    case '4':
                        for(unsigned int i = 0; i < 6; i++){
                            char value = getNextParamter();
                            
                            pinNumber += int (value);
                        }

                        hwlib::cout << duePins.read(pinNumber);

                    //flush()
                    case '5':
                        for(unsigned int i = 0; i < 6; i++){
                            char value = getNextParamter();
                            
                            pinNumber += int (value);
                        }

                        duePins.flush(pinNumber);

                    //refresh()
                    case '6':
                        for(unsigned int i = 0; i < 6; i++){
                            char value = getNextParamter();
                            
                            pinNumber += int (value);
                        }

                        duePins.refresh(pinNumber);
                }

            //pin_oc
            case '6':
            //pin_out
            case '7':
                // switch(function){
                //     //Constructor call, enable pin as output
                //     case 'c':

                //     //pin_out.write()
                //     case '1':

                //     //pin_out.flush()
                //     case '2':
                // }
            case '8':
            case '9':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            default:
                continue;

        }
    }

    
}