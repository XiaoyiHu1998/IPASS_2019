#ifndef DUE_PINS_HPP
#define DUE_PINS_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;


class duePins{
private:
    target::pin_in_out pins[54];
    uint8_t direction[54];
public:
    duePins():
        pins {
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
        },
        direction {
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            3, 3, 3, 3
        }
    {}

    void setOutput(int pin){
        pins[pin].direction_set_output();
        direction[pin] = 0;
    }

    void write(int pin, bool value){
        if(direction[pin] != 0){
            setOutput(pin);
        }
        pins[pin].write(value);
    }

    void setInput(int pin){
        pins[pin].direction_set_input();
        direction[pin] = 1;
    }

    char read(int pin){
        if(direction[pin] != 1){
            setInput(pin);
        }
        
        if(pins[pin].read()){
            return '1';
        }
        else if(!pins[pin].read()){
            return '0';
        }
        else{
            return 'e';
        }
    }

    void flush(int pin){
        pins[pin].flush();
    }

    void refresh(int pin){
        pins[pin].refresh();
    }
};

#endif //DUE_PINS_HPP
