#ifndef HWLIB_ARDUINO_DUE_REMOTE_H
#define HWLIB_ARDUINO_DUE_REMOTE_H

#include "/home/xiaoyi/Desktop/IPASS_2019/Code/PC/Linux/serialPort_linux.hpp"

char path[13] = "/dev/ttyUSB0";
serialPort_linux serialPort(path);

namespace due_remote{

enum pins : uint8_t {
   d0, d1, d2, d3, d4, d5, d6, d7, d8, d9,
   d10, d11, d12, d13, d14, d15, d16, d17, d18, d19,
   d20, d21, d22, d23, d24, d25, d26, d27, d28, d29,
   d30, d31, d32, d33, d34, d35, d36, d37, d38, d39,
   d40, d41, d42, d43, d44, d45, d46, d47, d48, d49,
   d50, d51, d52, d53,

   a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11,

   dac0, dac1, canrx, cantx,

   scl, sda, scl1, sda1,

   tx, rx, led, 

   sck, miso, mosi, cs0, cs1,

   /// \cond INTERNAL    
   SIZE_THIS_IS_NOT_A_PIN
   /// \endcond   
};

class pin_out : public hwlib::pin_out{
private:
   pins number;

   void selectClass(){
      serialPort.writeChar('5', 1);
   }

   void selectPin(){
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

   void sendStartBit(){
      serialPort.writeInt(200, 1);
   }

   void sendEndBit(){
      serialPort.writeInt(210, 1);
   }

public:
   pin_out(pins ENUMber){
                        number = ENUMber;
                        sendStartBit();
                        selectClass();
                        serialPort.writeChar('1', 1);
                        selectPin();
                        sendEndBit();
   }

   void write(bool v) override {
      sendStartBit();
      selectClass();
      serialPort.writeChar('3', 1);
      selectPin();

      if(v){
         serialPort.writeInt('a', 1);
      }
      else{
         serialPort.writeInt('b', 1);
      }
      sendEndBit();
   }

   void flush() override {
      sendStartBit();
      selectClass();
      serialPort.writeChar('5', 1);
      selectPin();
      sendEndBit();
   }
};

}; // namespace due_remote

#endif //HWLIB_ARDUINO_DUE_REMOTE_H