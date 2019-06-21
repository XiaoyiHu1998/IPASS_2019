#include "hwlib.hpp"
namespace target = hwlib::target;
 
Pio & __attribute__((weak)) port_registers( uint32_t port ){
   
   // a bit of a hack to put this here:

   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;

   // enable the clock to all GPIO ports
   PMC->PMC_P2CER0 = ( 0x3F << 11 );  

   switch( port ){
      case 0  : return *PIOA;
      case 1  : return *PIOB;
      case 2  : return *PIOC;
      case 3  : return *PIOD;
      default : break;
   }  
   
   // doesn't return   
   HWLIB_PANIC_WITH_LOCATION; 
}

void setPinIO(bool io){
    uint8_t port;
    uint8_t pin;
    hwlib::cin >> port;
    hwlib::cin >> pin;

    Pio & port = port;
    uint32_t mask = 0x1U << pin;

    (io ? port.PIO_ODR : port.PIO_OER) = mask;
}

void setOutput(){
    uint8_t port;
    uint8_t pin;
    uint_8_t io;
    hwlib::cin >> port;
    hwlib::cin >> pin;
    hwlib::cin >> io;

    Pio & port = port;
    uint32_t mask = 0x1U << pin;

    //set ouptut pin high
    if(io == '1'){
        port.SODR = mask;
    }
    //set output pin low
    else if(io == '0'){
        port.CODR = mask;
    }
}

void flush(){}

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
                switch(funtion){
                    //constructor call, enable pin as input
                    case 'c':
                        setPinIO(1);
                    
                    //pin_in.write()
                    case '1':
                        setOutput();
                        
                    //pin_in.flush()
                    case '2':
                        flush();
                }
            //pin_in_out
            case '5':
            //pin_oc
            case '6':
            //pin_out
            case '7':
                switch(function){
                    //Constructor call, enable pin as output
                    case 'c':
                        setPinIO(0);

                    //pin_out.write()
                    case '1':

                    //pin_out.flush()
                    case '2':
                }
            case '8':
            case '9':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'z':
                continue;

        }
        classChar = 'z';
    }

    
}