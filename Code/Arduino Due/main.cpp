#include "hwlib.hpp"
#include "duePins.h"

namespace target = hwlib::target;

char getNextChar(){
    return hwlib::cin.getc();
}

uint8_t getPinNumber(){
    return static_cast<uint8_t>(hwlib::cin.getc());
}

void toggle(duePins & pins, uint8_t pin, bool & on){
    if(on){
        pins.write(pin, 0);
        on = 0;
    }
    else{
        pins.write(pin, 1);
        on = 1;
    }
}

void blink(duePins & pins, uint8_t pin, bool & on){
    pins.write(pin ,1);
    hwlib::wait_ms(100);
    pins.write(pin ,0);
    hwlib::wait_ms(100);
}

void checkStartByte(duePins & IO, bool on2, bool on3){
    while(1){
        toggle(IO, 7, on2);
        if(getPinNumber() == 200){
            toggle(IO, 2, on3);
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

void initialBlink(duePins & IO, bool on){
    for(int i =0; i < 4; i++){
        blink(IO, 53, on);
        hwlib::wait_ms(100);
    }
}



int main(){
    duePins IO;
    
    bool on = 0;
    bool on2 = 0;
    bool on3 = 0;

    char classChar;
    char functionChar;
    uint8_t pinNumber;
    char writeValue;

    IO.setOutput(53);
    IO.setOutput(2);
    IO.setOutput(7);
    IO.setOutput(8);

    initialBlink(IO, on);


    while(1){
        checkStartByte(IO, on2, on3);
        classChar = getNextChar();

        switch(classChar){
            case '5':
                functionChar = getNextChar();
                pinNumber = getPinNumber();

                switch(functionChar){
                    //setOutput()
                    case '1':
                        IO.setOutput(pinNumber);
                        break;

                    //setInput()
                    case '2':
                        IO.setInput(pinNumber);
                        break;

                    //write()
                    case '3':
                        writeValue = getNextChar();

                        if(writeValue == 'a'){
                            IO.write(pinNumber, 1);
                            IO.flush(pinNumber);
                        }
                        else{
                            IO.write(pinNumber, 0);
                            IO.flush(pinNumber);
                        }
                        break;

                    //read()
                    case '4':
                        hwlib::cout << IO.read(pinNumber);
                        break;

                    //flush()
                    case '5':
                        IO.flush(pinNumber);
                        break;

                    //refresh()
                    case '6':
                        IO.refresh(pinNumber);
                        break;
                }

            checkEndByte();
            break;
        }
    } 
}