#ifndef HWLIB_ARDUINO_REMOTE_H
#define HWLIB_ARDUINO_REMOTE_H

#include "serialPort_linux.h"
#include <bitset>

namespace due_remote{

struct ad_pin_info_type{
   uint8_t channel;
};


class d2_36kHz : public hwlib::pin_out{
private:
   void selectClass(){
      port.writeData('2', 1);
   }
public:
   //write command to serial bus to construct a d2_36kHz object
   d2_36kHz(){
      
   }

   //write command to serial bus to do d2_36kHz.write(bool b)
   void write(bool b){
      selectClass();
      port.writeData('1', 1);

      if(b){
         port.writeData('1', 1);
      }
      else{
         port.writeData('0', 1);
      }
   }
}


class pin_out : public hwlib::pin_out{
private:
   uint8_t port;
   uint8_t pin;

   void selectClass(){
      port.Datawrite('7', 1);
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
                        port.writeData('7', 1);
                        port.writeData('c', 1);
                        port.writeData(port, 1);
                        port.writeData(pin, 1);
                     } 

   void write(bool v) override {
      selectClass();
      port.writeData('1', 1);

      port.writeData(port, 1);
      port.writeData(pin, 1);

      if(v){
         port.writeData('1', 1);
      }
      else{
         port.writeData('0', 1);
      }
   }

   flush() override {
      selectClass();
      port.writeData('2', 1);
   }
};

}; // namespace due_remote

#endif HWLIB_ARDUINO_REMOTE_H