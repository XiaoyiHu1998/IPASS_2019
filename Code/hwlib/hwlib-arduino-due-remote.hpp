#ifndef HWLIB_ARDUINO_DUE_REMOTE_H
#define HWLIB_ARDUINO_DUE_REMOTE_H

#include "/home/xiaoyi/Desktop/IPASS_2019/Code/PC/Linux/serialPort_linux.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/PC/Linux/serialPort_linux_path.hpp"

//======================================================================

serialPort_linux serialPort(path);

//======================================================================

namespace due_remote_primitives{

class pin_in_out{
public:
   virtual void direction_set_output() = 0;
   virtual void direction_set_input() = 0;
   virtual void direction_flush() = 0;
   virtual bool read() = 0;
   virtual void refresh() = 0;
   virtual void write(bool v) = 0;
   virtual void flush() = 0;
};

class pin_out{
public:
   virtual void write(bool v) = 0;
   virtual void flush() = 0;
};

class pin_in{
public:
   virtual bool read() = 0;
   virtual void refresh() = 0;
};

class pin_oc{
   virtual bool read() = 0;
   virtual void write(bool v) = 0;
   virtual void flush() = 0;
   virtual void refresh() = 0;
};

class pin_adc{
   virtual uint16_t read() = 0;
   virtual void refresh() = 0;
};


// ==========================================================================
//
// input / output port
//
// ==========================================================================


class port_in_out {
public:

   virtual uint_fast8_t number_of_pins() = 0;
   
   virtual void direction_set_input() = 0;   
   
   virtual uint_fast16_t read() = 0;         
   
   virtual void refresh() = 0;

   virtual void direction_set_output() = 0;

   virtual void write( uint_fast16_t x ) = 0;     
   
   virtual void flush() = 0;  
   
   virtual void direction_flush() = 0;

};
   
   
// ==========================================================================
//
// input port
//
// ==========================================================================

class port_in {
public:

   virtual uint_fast8_t number_of_pins() = 0;
   
   virtual uint_fast16_t read() = 0; 

   virtual void refresh() = 0;

};


// ==========================================================================
//
// output port
//
// ==========================================================================

class port_out {
public:

   virtual uint_fast8_t number_of_pins() = 0;
   
   virtual void write( uint_fast16_t x ) = 0;     
   
   virtual void flush() = 0;      

};

};

//======================================================================

namespace due_remote{

//======================================================================

void waitForStartSignal(){
   std::cout << "Serialport: " << path << std::endl;
   std::cout << "waiting for start signal from arduino" << std::endl << std::endl;
   char startupSignal;
   for(;;){
      startupSignal = serialPort.readChar();
      if(startupSignal == 's'){
         break;
      }
   }
}

//======================================================================

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

   dummy_in_out, dummy_in, dummy_out,

   /// \cond INTERNAL    
   SIZE_THIS_IS_NOT_A_PIN
   /// \endcond   
};

enum adc_pins : uint8_t{
   ad0, ad1, ad2, ad3, ad4, ad5, ad6, ad7, ad8, ad9, ad10,
   ad11,
   AD_SIZE_THIS_IS_NOT_A_PIN
};

//======================================================================

union adc_data{
    uint8_t uint8[2];
    uint16_t uint16;
};

//======================================================================

class pin_in_out_dummy : public due_remote_primitives::pin_in_out{
public:
   virtual void direction_set_output(){}
   virtual void direction_set_input(){}
   virtual void direction_flush(){}
   virtual bool read(){return 0;}
   virtual void refresh(){}
   virtual void write(bool v){}
   virtual void flush(){}
};

class pin_in_out : public due_remote_primitives::pin_in_out{
private:
   pins number;

   void selectClass(){
      serialPort.writeChar('1', 1);
   }

   void selectPin(){
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

   void sendStartByte(){
      serialPort.writeInt(200, 1);
   }

public:
   pin_in_out(pins ENUMber){
                        number = ENUMber;
                        }

   void direction_set_output() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('1', 1);
      selectPin();
   }
   
   void direction_set_input() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('2', 1);
      selectPin();
   }

   void direction_flush() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('7', 1);
      selectPin();
   }

   bool read() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('4', 1);
      selectPin();
      // sendEndByte();
      return serialPort.readBool();
      
   }

   void refresh() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('6', 1);
      selectPin();
      // sendEndByte();
   }

   void write(bool v) override{
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
      // sendEndByte();
   }

   void flush() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('5', 1);
      selectPin();
      // sendEndByte();
   }

};

class pin_out_dummy : public due_remote_primitives::pin_out{
public:
   virtual void write(bool v){}

   virtual void flush(){}
};

class pin_out : public due_remote_primitives::pin_out{
private:
   pins number;

   void selectClass(){
      serialPort.writeChar('1', 1);
   }

   void selectPin(){
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

   void sendStartByte(){
      serialPort.writeInt(200, 1);
   }

public:
   pin_out(pins ENUMber){
                        number = ENUMber;
                        }

   void write(bool v) override{
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
      // sendEndByte();
   }

   void flush() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('5', 1);
      selectPin();
      // sendEndByte();
   }
};


class pin_in_dummy : public due_remote_primitives::pin_in{
public:
   virtual bool read(){return 0;}

   virtual void refresh(){}
};

class pin_in : public due_remote_primitives::pin_in{
private:
   pins number;

   void selectClass(){
      serialPort.writeChar('1', 1);
   }

   void selectPin(){
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

   void sendStartByte(){
      serialPort.writeInt(200, 1);
   }
   
public:
   pin_in(pins ENUMber){
                        number = ENUMber;
                        }

   bool read() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('4', 1);
      selectPin();
      // sendEndByte();
      return serialPort.readBool();
      
   }

   void refresh() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('6', 1);
      selectPin();
      // sendEndByte();
   }
};

class pin_oc_dummy : public due_remote_primitives::pin_oc{
public:
   bool read() override {return 0;}

   void write(bool v) override {}

   void flush() override {}

   void refresh() override{}
};

class pin_adc_dummy : due_remote_primitives::pin_adc{
public:
   uint16_t read() override {return 0;}
   void refresh() override {}
};

class pin_adc : public due_remote_primitives::pin_adc{
private:
   adc_pins number;

   void selectClass(){
      serialPort.writeChar('2', 1);
   }

   void selectPin(){
      serialPort.writeInt(number, 1);
      std::cout << static_cast<uint16_t>(number) << ", ";
   }

   void sendStartByte(){
      serialPort.writeInt(200, 1);
   }

public:
   pin_adc(adc_pins ENUMber){
      number = ENUMber;
   }

   uint16_t read() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('1', 1);
      selectPin();
      adc_data reading;
      reading.uint8[0] = static_cast<uint8_t>(serialPort.readChar());
      reading.uint8[1] = static_cast<uint8_t>(serialPort.readChar());
      return reading.uint16;
      // sendEndByte();
   }

   void refresh() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('2', 1);
      selectPin();
      // sendEndByte();
   }
};

//======================================================================

pin_in_out_dummy in_in_out_dummy;
pin_out_dummy in_out_dummy;
pin_in_dummy in_in_dummy;

class all_from_pin_out_t : due_remote_primitives::pin_out{
private:
   static constexpr int max_pins = 16; 
   due_remote_primitives::pin_out * pins[max_pins];
public:
   all_from_pin_out_t(
                        due_remote_primitives::pin_out & p0 = in_out_dummy,
                        due_remote_primitives::pin_out & p1 = in_out_dummy,
                        due_remote_primitives::pin_out & p2 = in_out_dummy,
                        due_remote_primitives::pin_out & p3 = in_out_dummy,
                        
                        due_remote_primitives::pin_out & p4 = in_out_dummy,
                        due_remote_primitives::pin_out & p5 = in_out_dummy,
                        due_remote_primitives::pin_out & p6 = in_out_dummy,
                        due_remote_primitives::pin_out & p7 = in_out_dummy,
                        
                        due_remote_primitives::pin_out & p8 = in_out_dummy,
                        due_remote_primitives::pin_out & p9 = in_out_dummy,
                        due_remote_primitives::pin_out & p10 = in_out_dummy,
                        due_remote_primitives::pin_out & p11 = in_out_dummy,

                        due_remote_primitives::pin_out & p12 = in_out_dummy,
                        due_remote_primitives::pin_out & p13 = in_out_dummy,
                        due_remote_primitives::pin_out & p14 = in_out_dummy,
                        due_remote_primitives::pin_out & p15 = in_out_dummy
                     ):
                        pins{
                           &p0, &p1, &p2, &p3,
                           &p4, &p5, &p6, &p7,
                           &p8, &p9, &p10, &p11,
                           &p12, &p13, &p14, &p15
                        }
                     {}
   
   void write(bool v) override{
      for(auto & pin : pins){
         pin->write(v);
      }
   }

   void flush() override{
      for (auto & pin : pins){
         pin->flush();
      }
   }
};


class all_from_port_out_t : due_remote_primitives::pin_out{
private:
   due_remote_primitives::port_out & slave;
public:
   all_from_port_out_t(
                        due_remote_primitives::port_out & slave
                     ):
                        slave(slave)
                     {}
   
   void write(bool v) override{
      slave.write( v ? 0xFF : 0x0 );
   }

   void flush() override{
      slave.flush();
   }
};


//======================================================================

class port_in_out_from_pins_t : public due_remote_primitives::port_in_out{
private:
   static constexpr int max_pins = 16;
 
   uint_fast8_t _number_of_pins;  
 
   due_remote_primitives::pin_in_out * pins[ max_pins ]; 

public:
   port_in_out_from_pins_t(
                              due_remote_primitives::pin_in_out & p0 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p1 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p2 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p3 = in_in_out_dummy,
                              
                              due_remote_primitives::pin_in_out & p4 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p5 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p6 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p7 = in_in_out_dummy,
                              
                              due_remote_primitives::pin_in_out & p8 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p9 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p10 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p11 = in_in_out_dummy,

                              due_remote_primitives::pin_in_out & p12 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p13 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p14 = in_in_out_dummy,
                              due_remote_primitives::pin_in_out & p15 = in_in_out_dummy
                           ):
                           pins{
                              &p0, &p1, &p2, &p3,
                              &p4, &p5, &p6, &p7,
                              &p8, &p9, &p10, &p11,
                              &p12, &p13, &p14, &p15
                           }
                           {
                              for(_number_of_pins = 0; _number_of_pins < max_pins; ++_number_of_pins){
                                 if(pins[_number_of_pins] == & in_in_out_dummy){
                                    break;
                                 }
                              }
                           }

   uint_fast8_t number_of_pins() override{
      return _number_of_pins;
   }
   
   void direction_set_input() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->direction_set_input();
      }
   } 
   
   uint_fast16_t read() override{
      uint_fast8_t result = 0;
      for(uint_fast8_t i = _number_of_pins - 1; i >= 0; --i){
         result = result << 1;
         if(pins[i]->read()){
            result |= 0x01;
         }
      }

      return result;
   }         
   
   void refresh() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->refresh();
      }
   }  

   void direction_set_output() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->direction_set_output();
      }
   }  
   void write( uint_fast16_t x ) override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->write((x & 0x01) != 0);
         x = x >> 1;
      }
   }      
   
   void flush() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->flush();
      }
   }   
   
   void direction_flush()  override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->direction_flush();
      }
   }  
};


class port_out_from_pins_t : public due_remote_primitives::port_out{
private:
   static constexpr int max_pins = 16;
 
   uint_fast8_t _number_of_pins;  
 
   due_remote_primitives::pin_out * pins[ max_pins ]; 

public:
   port_out_from_pins_t(
                        due_remote_primitives::pin_out & p0 = in_out_dummy,
                        due_remote_primitives::pin_out & p1 = in_out_dummy,
                        due_remote_primitives::pin_out & p2 = in_out_dummy,
                        due_remote_primitives::pin_out & p3 = in_out_dummy,
                        
                        due_remote_primitives::pin_out & p4 = in_out_dummy,
                        due_remote_primitives::pin_out & p5 = in_out_dummy,
                        due_remote_primitives::pin_out & p6 = in_out_dummy,
                        due_remote_primitives::pin_out & p7 = in_out_dummy,
                        
                        due_remote_primitives::pin_out & p8 = in_out_dummy,
                        due_remote_primitives::pin_out & p9 = in_out_dummy,
                        due_remote_primitives::pin_out & p10 = in_out_dummy,
                        due_remote_primitives::pin_out & p11 = in_out_dummy,

                        due_remote_primitives::pin_out & p12 = in_out_dummy,
                        due_remote_primitives::pin_out & p13 = in_out_dummy,
                        due_remote_primitives::pin_out & p14 = in_out_dummy,
                        due_remote_primitives::pin_out & p15 = in_out_dummy
                     ):
                     pins{
                        &p0, &p1, &p2, &p3,
                        &p4, &p5, &p6, &p7,
                        &p8, &p9, &p10, &p11,
                        &p12, &p13, &p14, &p15
                     }
                     {
                        for(_number_of_pins = 0; _number_of_pins < max_pins; ++_number_of_pins){
                           if(pins[_number_of_pins] == & in_out_dummy){
                              break;
                           }
                        }
                     }

   uint_fast8_t number_of_pins() override{
      return _number_of_pins;
   }

   void write( uint_fast16_t x ) override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->write((x & 0x01) != 0);
         x = x >> 1;
      }
   }      
   
   void flush() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->flush();
      }
   }
};

class port_in_from_pins_t : public due_remote_primitives::port_in{
private:
   static constexpr int max_pins = 16;
 
   uint_fast8_t _number_of_pins;  
 
   due_remote_primitives::pin_in * pins[ max_pins ]; 

public:
   port_in_from_pins_t(
                        due_remote_primitives::pin_in & p0 = in_in_dummy,
                        due_remote_primitives::pin_in & p1 = in_in_dummy,
                        due_remote_primitives::pin_in & p2 = in_in_dummy,
                        due_remote_primitives::pin_in & p3 = in_in_dummy,
                        
                        due_remote_primitives::pin_in & p4 = in_in_dummy,
                        due_remote_primitives::pin_in & p5 = in_in_dummy,
                        due_remote_primitives::pin_in & p6 = in_in_dummy,
                        due_remote_primitives::pin_in & p7 = in_in_dummy,
                        
                        due_remote_primitives::pin_in & p8 = in_in_dummy,
                        due_remote_primitives::pin_in & p9 = in_in_dummy,
                        due_remote_primitives::pin_in & p10 = in_in_dummy,
                        due_remote_primitives::pin_in & p11 = in_in_dummy,

                        due_remote_primitives::pin_in & p12 = in_in_dummy,
                        due_remote_primitives::pin_in & p13 = in_in_dummy,
                        due_remote_primitives::pin_in & p14 = in_in_dummy,
                        due_remote_primitives::pin_in & p15 = in_in_dummy
                     ):
                     pins{
                        &p0, &p1, &p2, &p3,
                        &p4, &p5, &p6, &p7,
                        &p8, &p9, &p10, &p11,
                        &p12, &p13, &p14, &p15
                     }
                     {
                        for(_number_of_pins = 0; _number_of_pins < max_pins; ++_number_of_pins){
                           if(pins[_number_of_pins] == & in_in_dummy){
                              break;
                           }
                        }
                     }

   uint_fast8_t number_of_pins() override{
      return _number_of_pins;
   }
   
   uint_fast16_t read() override{
      uint_fast8_t result = 0;
      for(uint_fast8_t i = _number_of_pins - 1; i >= 0; --i){
         result = result << 1;
         if(pins[i]->read()){
            result |= 0x01;
         }
      }

      return result;
   }         
   
   void refresh() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->refresh();
      }
   }
};


//======================================================================

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