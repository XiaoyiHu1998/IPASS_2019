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

enum adc_pins : uint8_t{
   ad0, ad1, ad2, ad3, ad4, ad5, ad6, ad7, ad8, ad9, ad10,
   ad11,
   AD_SIZE_THIS_IS_NOT_A_PIN
};

union adc_data{
    uint8_t uint8[2];
    uint16_t uint16;
};

class pin{
protected:
   virtual void selectClass() = 0;

   virtual void selectPin() = 0;

   void sendStartByte(){
      serialPort.writeInt(200, 1);
   }

   void sendEndByte(){
      serialPort.writeInt(210, 1);
   }
};

class remote_pin_in_out : public pin{
public:
   virtual void write(bool v){}
   virtual bool read(){return 0;}
   virtual void flush(){}
   virtual void refresh(){}
};

class pin_in_out : public remote_pin_in_out{
private:
   pins number;

   void selectClass() override {
      serialPort.writeChar('1', 1);
   }

   void selectPin() override {
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

public:
   pin_in_out(pins ENUMber){
                        number = ENUMber;
                        }

   bool read() override {
      
      sendStartByte();
      selectClass();
      serialPort.writeChar('4', 1);
      selectPin();
      sendEndByte();
      return serialPort.readBool();
      
   }

   void refresh() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('6', 1);
      selectPin();
      sendEndByte();
   }

   void write(bool v) override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('3', 1);
      selectPin();

      if(v){
         serialPort.writeInt('a', 1);
      }
      else{
         serialPort.writeInt('b', 1);
      }
      sendEndByte();
   }

   void flush() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('5', 1);
      selectPin();
      sendEndByte();
   }
};


class pin_out : public remote_pin_in_out{
private:
   pins number;

   void selectClass(){
      serialPort.writeChar('5', 1);
   }

   void selectPin(){
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

public:
   pin_out(pins ENUMber){
                        number = ENUMber;
                        }

   void write(bool v) override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('3', 1);
      selectPin();

      if(v){
         serialPort.writeInt('a', 1);
      }
      else{
         serialPort.writeInt('b', 1);
      }
      sendEndByte();
   }

   void flush() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('5', 1);
      selectPin();
      sendEndByte();
   }
};

class pin_in : public remote_pin_in_out{
private:
   pins number;

   void selectClass() override {
      serialPort.writeChar('5', 1);
   }

   void selectPin() override {
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

public:
   pin_in(pins ENUMber){
                        number = ENUMber;
                        }

   bool read() override {
      
      sendStartByte();
      selectClass();
      serialPort.writeChar('4', 1);
      selectPin();
      sendEndByte();
      return serialPort.readBool();
      
   }

   void refresh() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('6', 1);
      selectPin();
      sendEndByte();
   }
};

class pin_adc : public pin{
private:
   adc_pins number;

   void selectClass(){
      serialPort.writeChar('2', 1);
   }

   void selectPin(){
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

public:
   pin_adc(adc_pins ENUMber){
      number = ENUMber;
   }

   uint16_t read(){
      sendStartByte();
      selectClass();
      serialPort.writeChar('1', 1);
      selectPin();
      adc_data reading;
      reading.uint8[0] = static_cast<uint8_t>(serialPort.readChar());
      reading.uint8[1] = static_cast<uint8_t>(serialPort.readChar());
      return reading.uint16;
      sendEndByte();
   }

   void refresh(){
      sendStartByte();
      selectClass();
      serialPort.writeChar('2', 1);
      selectPin();
      sendEndByte();
   }
};

//get input from console screen
char uart_getc(){
   char character;
   std::cin >> character;
   return character;
}

//output character to console screen.
void uart_putc(char character){
   hwlib::cout << character;
}

}; // namespace due_remote

#endif //HWLIB_ARDUINO_DUE_REMOTE_H