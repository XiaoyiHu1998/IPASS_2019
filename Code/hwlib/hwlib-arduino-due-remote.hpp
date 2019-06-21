#ifndef HWLIB_ARDUINO_DUE_REMOTE_H
#define HWLIB_ARDUINO_DUE_REMOTE_H

#include "/home/xiaoyi/Desktop/IPASS_2019/Code/PC/Linux/serialPort_linux.h"
#include <bitset>

char path[13] = "/dev/ttyUSB0";
serialPort_linux serialPort(path);

namespace due_remote{

enum class pins {
   d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, 
   d11, d12, d13, d14, d15, d16, d17, d18, d19, d20,
   d21, d22, d23, d24, d25, d26, d27, d28, d29, d30,
   d31, d32, d33, d34, d35, d36, d37, d38, d39, d40,
   d41, d42, d43, d44, d45, d46, d47, d48, d49, d50,
   d51, d52, d53, 
   a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11,
   dac0, dac1, canrx, cantx,
   scl, sda, scl1, sda1,
   tx, rx, led, 
   sck, miso, mosi, cs0, cs1,
/// \cond INTERNAL    
   SIZE_THIS_IS_NOT_A_PIN
/// \endcond   
};


/// \cond INTERNAL 

struct pin_info_type { 
   uint8_t port; 
   uint8_t pin; 
};  

const HWLIB_WEAK pin_info_type & pin_info( pins name ){
   
   static const pin_info_type pin_info_array[ (int) pins::SIZE_THIS_IS_NOT_A_PIN ] = {
      { 0,  8 },  // d0
      { 0,  9 },  // d1
      { 1, 25 },  // d2
      { 2, 28 },  // d3
      { 2, 26 },  // d4
      { 2, 25 },  // d5
      { 2, 24 },  // d6
      { 2, 23 },  // d7
      { 2, 22 },  // d8
      { 2, 21 },  // d9
      { 2, 29 },  // d10
   
      { 3,  7 },  // d11
      { 3,  8 },  // d12
      { 1, 27 },  // d13
      { 3,  4 },  // d14
      { 3,  5 },  // d15
      { 0, 13 },  // d16
      { 0, 12 },  // d17
      { 0, 11 },  // d18
      { 0, 10 },  // d19
      { 1, 12 },  // d20
   
      { 1, 13 },  // d21
      { 1, 26 },  // d22
      { 0, 14 },  // d23
      { 0, 15 },  // d24
      { 3,  0 },  // d25
      { 3,  1 },  // d26
      { 3,  2 },  // d27
      { 3,  3 },  // d28
      { 3,  6 },  // d29
      { 3,  9 },  // d30

      { 0,  7 },  // d31
      { 3, 10 },  // d32
      { 2,  1 },  // d33
      { 2,  2 },  // d34
      { 2,  3 },  // d35
      { 2,  4 },  // d36
      { 2,  5 },  // d37
      { 2,  6 },  // d38
      { 2,  7 },  // d39
      { 2,  8 },  // d40

      { 2,  9 },  // d41
      { 0, 19 },  // d42
      { 0, 20 },  // d43
      { 2, 19 },  // d44
      { 2, 18 },  // d45
      { 2, 17 },  // d46
      { 2, 16 },  // d47
      { 2, 15 },  // d48
      { 2, 14 },  // d49
      { 2, 13 },  // d50
   
      { 2, 12 },  // d51
      { 1, 21 },  // d52
      { 1, 14 },  // d53
   
      { 0, 16 },  // a0
      { 0, 24 },  // a1
      { 0, 23 },  // a2
      { 0, 22 },  // a3
      { 0,  6 },  // a4
      { 0,  4 },  // a5
      { 0,  3 },  // a6
      { 0,  2 },  // a7
      { 1, 17 },  // a8
      { 1, 18 },  // a9
      { 1, 19 },  // a10
      { 1, 20 },  // a11
   
      { 1, 15 },  // dac0
      { 1, 16 },  // dac1
      { 0,  1 },  // cantx
      { 0,  0 },  // canrx
   
      { 1, 13 },  // scl
      { 1, 12 },  // sda
      { 0, 18 },  // scl1
      { 0, 17 },  // sda1
   
      { 0,  9 },  // tx
      { 0,  8 },  // rx
      { 1, 27 },  // led

      { 0, 27 },  // sck
      { 0, 25 },  // miso
      { 0, 26 },  // mosi
      { 2, 29 },  // cs0
      { 2, 26 }   // cs1
   };    
   
   uint_fast8_t n = static_cast< uint_fast8_t>( name );
   if( n >= static_cast< uint_fast8_t>( pins::SIZE_THIS_IS_NOT_A_PIN )){
      HWLIB_PANIC_WITH_LOCATION;
   }
   return pin_info_array[ n ];
}

/// \endcond  


/// Arduino Due pin names
/// 
/// These are the ADC pins of an Arduino Due board.
enum class ad_pins {
   a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11
/// \cond INTERNAL    
   ,AD_SIZE_THIS_IS_NOT_A_PIN
/// \endcond   
};

/// definition of an A/D input
struct ad_pin_info_type {
   
   /// the channel number
   uint8_t channel;
};

class d2_36kHz : public hwlib::pin_out{
private:
   void selectClass(){
      serialPort.writeData("2", 1);
   }
public:
   //write command to serial bus to construct a d2_36kHz object
   d2_36kHz(){
      
   }

   //write command to serial bus to do d2_36kHz.write(bool b)
   void write(bool b) override{
      selectClass();
      serialPort.writeData("1", 1);

      if(b){
         serialPort.writeData("1", 1);
      }
      else{
         serialPort.writeData("0", 1);
      }
   }
};


class pin_out : public hwlib::pin_out{
private:
   uint8_t port;
   uint8_t pin;

   void selectClass(){
      serialPort.writeData("7", 1);
   }
public:
   // pin_out(uint32_t port_number, uint32_t pin_number):
   //                                                    port{ port_registers( port_number ) }, 
   //                                                    mask{ 0x1U << pin_number }
   //                                                    {
   //                                                       port.writeData();
   //                                                    }

   pin_out(pins name):
                     port(pin_info(name).port), 
                     pin(pin_info(name).pin)
                     {
                        serialPort.writeData("7", 1);
                        serialPort.writeData("c", 1);
                        serialPort.writeData(&port, 1);
                        serialPort.writeData(&pin, 1);
                     } 

   void write(bool v) override {
      selectClass();
      serialPort.writeData("1", 1);

      serialPort.writeData(&port, 1);
      serialPort.writeData(&pin, 1);

      if(v){
         serialPort.writeData("1", 1);
      }
      else{
         serialPort.writeData("0", 1);
      }
   }

   void flush() override {
      selectClass();
      serialPort.writeData("2", 1);
   }
};

}; // namespace due_remote

#endif //HWLIB_ARDUINO_DUE_REMOTE_H