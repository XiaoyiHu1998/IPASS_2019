#include "hwlib.hpp"
#include "duePins.h"

namespace target = hwlib::target;

char getNextChar(){
    return hwlib::cin.getc();
}

uint8_t getPinNumber(){
    return static_cast<uint8_t>(hwlib::cin.getc());
}

void toggle(in_out_pins & pins, uint8_t pin, bool & on){
    if(on){
        pins.write(pin, 0);
        on = 0;
    }
    else{
        pins.write(pin, 1);
        on = 1;
    }
}

void blink(in_out_pins & pins, uint8_t pin, bool & on){
    pins.write(pin ,1);
    hwlib::wait_ms(100);
    pins.write(pin ,0);
    hwlib::wait_ms(100);
}

void checkStartByte(in_out_pins & GPIO, bool on2, bool on3){
    while(1){
        toggle(GPIO, 7, on2);
        if(getPinNumber() == 200){
            toggle(GPIO, 2, on3);
            break;
        }
    }
}

void checkEndByte(){
    while(1){
        if(getPinNumber() == 210){
            break;
        }
    }
}

void initialBlink(in_out_pins & GPIO, bool on){
    for(int i =0; i < 4; i++){
        blink(GPIO, 6, on);
        hwlib::wait_ms(100);
    }
}

void sendStartSignal(){
    hwlib::cout << 's';
}



int main(){
    in_out_pins GPIO;
    adc_pins ADIO;
    
    bool on = 0;
    bool on2 = 0;
    bool on3 = 0;

    char classChar;
    char functionChar;
    uint8_t pinNumber;
    char writeValue;

    initialBlink(GPIO, on);

    sendStartSignal();


    while(1){
        checkStartByte(GPIO, on2, on3);
        classChar = getNextChar();

        switch(classChar){
            //pin_in_out, pin_in, pin_out
            case '1':
                functionChar = getNextChar();
                pinNumber = getPinNumber();

                switch(functionChar){
                    //setOutput()
                    case '1':
                        GPIO.setOutput(pinNumber);
                        break;

                    //setInput()
                    case '2':
                        GPIO.setInput(pinNumber);
                        break;

                    //write()
                    case '3':
                        writeValue = getNextChar();

                        if(writeValue == 'a'){
                            GPIO.write(pinNumber, 1);
                            GPIO.flush(pinNumber);
                        }
                        else{
                            GPIO.write(pinNumber, 0);
                            GPIO.flush(pinNumber);
                        }
                        break;

                    //read()
                    case '4':
                        GPIO.refresh(pinNumber);
                        hwlib::cout << GPIO.read(pinNumber);
                        break;

                    //flush()
                    case '5':
                        GPIO.flush(pinNumber);
                        break;

                    //refresh()
                    case '6':
                        GPIO.refresh(pinNumber);
                        break;

                    //direction_flush()
                    case '7':
                        GPIO.flushDirection(pinNumber);
                }
                break;

            //pin_adc
            case '2':
                functionChar = getNextChar();
                pinNumber = getPinNumber();
                switch(functionChar){
                    //read
                    case '1':
                        ADIO.read(pinNumber);
                        break;

                    //refresh
                    case '2':
                        ADIO.refresh(pinNumber);
                        break;
                }
                break;
        
        // checkEndByte();
        break;
        }
    } 
}