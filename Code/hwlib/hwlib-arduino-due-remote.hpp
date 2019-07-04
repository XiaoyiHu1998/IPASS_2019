// ==========================================================================
//
// File      : hwlib-due-remote.hpp
// Part of   : C++ hwlib extension library for close-to-the-hardware OO programming
// Copyright : xy1998@live.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_ARDUINO_DUE_REMOTE_H
#define HWLIB_ARDUINO_DUE_REMOTE_H

#include "/home/xiaoyi/Desktop/IPASS_2019/Code/PC/Linux/serialPort_linux.hpp"
#include "/home/xiaoyi/Desktop/IPASS_2019/Code/PC/Linux/serialPort_linux_path.hpp"

/// \brief
/// hwlib extension for remote access and control to GPIO pins on Arduino Due's
/// 
/// \image html due-pcb.jpg
//
/// The due_remote_primitives namespaces contains abstract superclasses for classes in
/// the due_remote namespace.
///
/// The class names are used are the same as those found in the hwlib::due namespace
/// as of June 2019 to maintain compatibility with existing programs using hwlib,
/// requiring only a change in target namespace to due_remote.
///
/// The Due has an on-board orange LED connected to port 1 pin 27.
///
/// The chip runs at 3.3 Volt and that is the level on its IO pins.
///
/// \image html due-pinout.png
///
/// The ATSAM3X8E chip has a watchdog system that is enabled by default.
/// If left alone, the watchdog will reset the chip after a short time. 
/// To prevent this, the watchdog is disabled on the first 
/// timing call (wait_*() or now_*()).
///
/// References:
///    - <A HREF="https://www.arduino.cc/en/uploads/Main/arduino-uno-schematic.pdf">
///       Arduino Due circuit reference diagram</A> (pdf)
///    - <A HREF="http://www.atmel.com/ru/ru/Images/Atmel-11057-32-bit-Cortex-M3-Microcontroller-SAM3X-SAM3A_Datasheet.pdf">
///       ATSAM38XE datasheet</A> (pdf)
///    - <A HREF="https://github.com/wovo/hwlib">
///      Original HWLIB repository

//======================================================================

serialPort_linux serialPort(path); //path for serialport declared in serialPort_linux_path.hpp

//======================================================================
///namespace due_remote_primitives contains abstract classes for due_remote classes
namespace due_remote_primitives{

///\brief abstract class for pin_in_out
class pin_in_out{
public:
   virtual void direction_set_output() = 0;
   virtual void direction_set_input() = 0;
   virtual void direction_flush() = 0;
   virtual bool read() = 0;
   virtual void refresh() = 0;
   virtual void write(bool v) = 0;
   virtual void flush() = 0;
   virtual void pullup_enable() = 0;
   virtual void pullup_disable() = 0;
};

///abstract class for pin_out
class pin_out{
public:
   virtual void write(bool v) = 0;
   virtual void flush() = 0;
};

///abstract class for pin_in
class pin_in{
public:
   virtual bool read() = 0;
   virtual void refresh() = 0;
   virtual void pullup_enable() = 0;
   virtual void pullup_disable() = 0;
};

///abstract class for pin_oc
class pin_oc{
   virtual bool read() = 0;
   virtual void write(bool v) = 0;
   virtual void flush() = 0;
   virtual void refresh() = 0;
};

///abstract class for pin_adc
class pin_adc{
   virtual uint16_t read() = 0;
   virtual void refresh() = 0;
};


//===========================input / output port===========================


///abstract class for port_in_out
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

   virtual void pullup_enable() = 0;

   virtual void pullup_disable() = 0;

};
   
//===============================input port================================

///abstract class for port_in
class port_in {
public:

   virtual uint_fast8_t number_of_pins() = 0;
   
   virtual uint_fast16_t read() = 0; 

   virtual void refresh() = 0;

   virtual void pullup_enable() = 0;

   virtual void pullup_disable() = 0;

};

// =============================output port================================

///abstract class for port_out
class port_out {
public:

   virtual uint_fast8_t number_of_pins() = 0;
   
   virtual void write( uint_fast16_t x ) = 0;     
   
   virtual void flush() = 0;      

};

};

//                     namespace: due_remote_primitives
//======================================================================



//======================================================================
//
//                             Due_remote
//
//======================================================================

///namespace due_remote contains all implemented classes for Arduino Due
namespace due_remote{

///function to make the program sync with Arduino Due at startup
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
//
//                           Enum Classes
//
//======================================================================

///Arduino Due GPIO pin names
///
/// These are the pins of an Arduino Due board.
/// Digital pins d0..d13, analog input pins A0..A5, 
/// SCL, SDA, TX (=D1), RX (=D0), 
/// LED (=D13), SCK (=D13), MISO (=D12), MOSI (=D11), SS (=D10).

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

///Arduino Due pin names
/// 
/// These are the ADC pins of an Arduino Due board.
enum adc_pins : uint8_t{
   ad0, ad1, ad2, ad3, ad4, ad5, ad6, ad7, ad8, ad9, ad10,
   ad11,
   AD_SIZE_THIS_IS_NOT_A_PIN
};

//========================adc_data data-type============================

//Union datatype used for data transfer from Arduino to PC for pin_adc.read() contains uint8_t uint8[2] array and uint16_t uint16
union adc_data{
    uint8_t uint8[2];
    uint16_t uint16;
};

//======================================================================
//
//                              pins
//
//======================================================================


//==========================Due_remote_primitives=======================

///pin_in_out_dummy, always reads and writes 0
class pin_in_out_dummy : public due_remote_primitives::pin_in_out{
public:
   void direction_set_output() override {}
   void direction_set_input() override {}
   void direction_flush() override {}
   bool read() override { return 0; }
   void refresh() override {}
   void write(bool v) override {}
   void flush() override {}
   void pullup_enable() override {}
   void pullup_disable() override {}
};

///pin_in_out implementation for remote Arduino Due
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

   /// Remote Arduino Due pin_in_out constructor
   /// 
   /// Constructor for a remote Arduino in and output pin
   ///
   /// ENUMber given is a member of enum class due_remote::pins
   /// ENUMbers refer to pin names on Arduino Board
   ///
   /// This constructor does not set the pin direction to in or output.
   pin_in_out(pins ENUMber){
                        number = ENUMber;
                        }

   ///\brief sets pin to output
   ///\details sets direction of pin to turn it into an output pins
   void direction_set_output() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('1', 1);
      selectPin();
   }
   
   ///\brief sets pin to input
   ///\details sets direction of pin to turn it into an input pin
   void direction_set_input() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('2', 1);
      selectPin();
   }

   ///\brief flushes pin direction
   ///\details changes value of signal comming out of the pin to the value most recently written to it
   void direction_flush() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('7', 1);
      selectPin();
   }
   
   ///\brief returns value on the pin
   ///\details returns value recieved form when the pin was last refreshed, will change direction if pin is set to output before read is called
   bool read() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('4', 1);
      selectPin();
      return serialPort.readBool();
      
   }

   ///\brief refreshes the input pin
   ///\details refreshes the value returned by pin to the current signal value on the pin
   void refresh() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('6', 1);
      selectPin();
   }

   ///\brief writes bool v to pin
   ///\details writes the given bool value to the pin which will be outputted after flush() is called, this function will change the pin to output if previously set to input
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
   }

   ///\brief flushes the pin
   ///\details flushes the pin to make it output the signal last written to it
   void flush() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('5', 1);
      selectPin();
   }

   ///\brief enables the pullup
   ///\details enables the weak pullup resistor on the pin
   void pullup_enable() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('8', 1);
      selectPin();
   }

   ///\brief disables the pullup
   ///\details disables the weak pullup resistor on the pin
   void pullup_disable() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('9', 1);
      selectPin();
   }

};

//===============================pin_out================================

///pin_in_out_dummy implementation for remote Arduino Due, always writes 0
class pin_out_dummy : public due_remote_primitives::pin_out{
public:
   ///\brief writes 0 to pin
   ///\details writes 0 to pin
   void write(bool v) override {}

   ///\brief flushes most recent written value onto the pin
   ///\flushes the pin to make it output the last value written to it
   void flush() override {}
};

///pin_out implementation for remote Arduino Due
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

   /// Remote Arduino Due pin_out constructor
   /// 
   /// Constructor for a remote Arduino output pin
   ///
   /// ENUMber given is a member of enum class due_remote::pins
   /// ENUMbers refer to pin names on Arduino Board

   pin_out(pins ENUMber){
                        number = ENUMber;
                        }

   ///\brief writes bool v to pin
   ///\details writes the given bool value to the pin which will be outputted after flush() is called, this function will change the pin to output if previously set to input
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
   }

   ///\brief flushes the pin
   ///\details flushes the pin to make it output the signal last written to it
   void flush() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('5', 1);
      selectPin();
   }
};

//===============================pin_in=================================

///pin_in_dummy implementation for remote Arduino Due, always reads 0
class pin_in_dummy : public due_remote_primitives::pin_in{
public:
   ///\brief always returns 0
   ///\details returns 0
   bool read() override {return 0;}

   ///\brief refreshes value on the pin
   ///\details refreshes value on the pin
   void refresh() override {}

   ///\brief enables the pullup
   ///\details enables the weak pullup resistor on the pin
   void pullup_enable() override {}

   ///\brief disables the pullup
   ///\details disables the weak pullup resistor on the pin
   void pullup_disable() override {}
};

///pin_in implementation for remote Arduino Due
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

   /// Remote Arduino Due pin_in constructor
   /// 
   /// Constructor for a remote Arduino input pin
   ///
   /// ENUMber given is a member of enum class due_remote::pins
   /// ENUMbers refer to pin names on Arduino Board

   pin_in(pins ENUMber){
                        number = ENUMber;
                        }

   ///\brief returns value on the pin
   ///\details returns value recieved form when the pin was last refreshed, will change direction if pin is set to output before read is called
   bool read() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('4', 1);
      selectPin();
      return serialPort.readBool();
      
   }

   ///\brief refreshes the input pin
   ///\details refreshes the value returned by pin to the current signal value on the pin
   void refresh() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('6', 1);
      selectPin();
   }

   ///\brief enables the pullup
   ///\details enables the weak pullup resistor on the pin
   void pullup_enable() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('8', 1);
      selectPin();
   }

   ///\brief disables the pullup
   ///\details disables the weak pullup resistor on the pin
   void pullup_disable() override {
      sendStartByte();
      selectClass();
      serialPort.writeChar('9', 1);
      selectPin();
   }
};

//=============================pin_oc_dummy=============================

///pin_oc_dummy implementation for remote Arduino Due, always reads and writes 0
class pin_oc_dummy : public due_remote_primitives::pin_oc{
public:
///\brief always returns 0
///\details always returns 0
   bool read() override {return 0;}

///\brief writes 0 to pin
///\details writes 0 to pin
   void write(bool v) override {}

///\details flushes value 0 to pin
///\details flushes value 0 to pin
   void flush() override {}

///\details reads value 0 on pin
///\details reads value 0 on pin
   void refresh() override{}
};

//======================pin_adc (not functional)========================

///pin_adc_dummy implementation for remote Arduino Due, always reads and writes 0
class pin_adc_dummy : due_remote_primitives::pin_adc{
public:
   ///\brief returns 0
   ///\details reutnrs 0
   uint16_t read() override {return 0;}

   ///\brief refreshes value on pin to 0
   ///\details refreshes value on pin to 0
   void refresh() override {}
};

///pin_adc implementation for remote Arduino Due, does not work properly
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

   /// Remote Arduino Due pin_adc constructor
   /// 
   /// Constructor for a remote Arduino adc pin
   ///
   /// ENUMber given is a member of enum class due_remote::pins
   /// ENUMbers refer to pin names on Arduino Board

   pin_adc(adc_pins ENUMber){
      number = ENUMber;
   }

   ///\brief returns value on adc pin
   ///\details returns uint16_t with value inbetween 0 and 4096, currently not functional
   uint16_t read() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('1', 1);
      selectPin();
      adc_data reading;
      reading.uint8[0] = static_cast<uint8_t>(serialPort.readChar());
      reading.uint8[1] = static_cast<uint8_t>(serialPort.readChar());
      return reading.uint16;
   }

   ///\brief refreshes adc pin
   ///\details redhreshes value returned by read to current value read on pin
   void refresh() override{
      sendStartByte();
      selectClass();
      serialPort.writeChar('2', 1);
      selectPin();
   }
};

//======================================================================
//
//                all_fromport_out_t / all_from_pin_out_t
//
//======================================================================

///pin_in_out object to give as default for constructors
pin_in_out_dummy in_in_out_dummy;
///pin_out object to give as default for constructors
pin_out_dummy in_out_dummy;
///pin_in object to give as default for constructors
pin_in_dummy in_in_dummy;

//==========================all_from_pin_out_t==========================

///implementation of all_from_port_out_t for remote Arduino Due
class all_from_pin_out_t : due_remote_primitives::pin_out{
private:
   static constexpr int max_pins = 16; 
   due_remote_primitives::pin_out * pins[max_pins];
public:

   /// Remote Arduino Due all_from_pin_out_t constructor
   /// 
   /// Constructor for a remote Arduino all_from_pin_out_t "pin"
   ///
   /// Takes a set of max 16 pin_outs and makes them addressable as one pin
   /// When given less than max pins pin_out_dummy's are used to fill out the leftover pins

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
   
   ///\brief writes given bool value to all pins
   ///\details writes given value to all pins in object
   void write(bool v) override{
      for(auto & pin : pins){
         pin->write(v);
      }
   }

   ///\brief flushes most recently written value to all pins
   ///\details flushes pins most recently written value to all pins in object
   void flush() override{
      for (auto & pin : pins){
         pin->flush();
      }
   }
};

//==========================all_from_port_out_t=========================

///implementation of all_from_port_out_t for remote Arduino Due
class all_from_port_out_t : due_remote_primitives::pin_out{
private:
   due_remote_primitives::port_out & slave;
public:

   /// Remote Arduino Due all_from_port_out_t constructor
   /// 
   /// Constructor for a remote Arduino all_from_pin_port_t "pin"
   ///
   /// Takes a port_out and makes them act as one pin

   all_from_port_out_t(
                        due_remote_primitives::port_out & slave
                     ):
                        slave(slave)
                     {}
   
   ///\brief writes given value to all pins on the port
   ///\details writes given value to all pins on port in object
   void write(bool v) override{
      slave.write( v ? 0xFF : 0x0 );
   }

   ///\brief writes most recently written value all pins on the port
   ///\details flushes pins most recently written value to all pins on port in object
   void flush() override{
      slave.flush();
   }
};


//======================================================================
//
//                               port_outs
//
//======================================================================

//========================port_in_out_from_pins_t=======================

///implementation of port_in_out_from_pins_t for remote Arduino Due
class port_in_out_from_pins_t : public due_remote_primitives::port_in_out{
private:
   static constexpr int max_pins = 16;
 
   uint_fast8_t _number_of_pins;  
 
   due_remote_primitives::pin_in_out * pins[ max_pins ]; 

public:

   /// Remote Arduino Due port_in_out_from_pins_t constructor
   /// 
   /// Constructor for a remote Arduino port_in_out_from_pins_t port
   ///
   /// Takes a set of max 16 pin_in_outs, and makes them adressable as a prt

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

   ///\brief returns the number of pins in the port
   ///\details returns uint_fast8_t that is equal to amount of pins put into port
   uint_fast8_t number_of_pins() override{
      return _number_of_pins;
   }
   
   ///\brief sets direction of pin_in_outs of the port to input
   ///\detials sets direction of all pins_outs of the port to input
   void direction_set_input() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->direction_set_input();
      }
   } 
   
   ///\brief returns uint_fast16_t value
   ///\details returns uint_fast16_t value with each bit representing the input value on the pins connected to port, changes pin direction if necesarry
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
   
   ///\brief refreshes pins of the port
   ///\brief refreshes values read on the pins of the port
   void refresh() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->refresh();
      }
   }  

   ///\sets direction of pin_in_outs of the port to ouput
   ///\detials sets direction of all pins_outs of the port to output
   void direction_set_output() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->direction_set_output();
      }
   }
   
   ///\brief writes given uint_fast16_t
   ///\brief writes given uint_fast16_t value onto the pins of the port, changes pin direction if necesarry
   void write( uint_fast16_t x ) override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->write((x & 0x01) != 0);
         x = x >> 1;
      }
   }      
   
   ///\brief flushes pins of the port
   ///\brief flushes most recent written values to pins of the port
   void flush() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->flush();
      }
   }   
   
   ///\brief flushes  pins of the port
   ///\brief flushes most recently given direction to the pins of the port
   void direction_flush()  override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->direction_flush();
      }
   }

   ///\brief enables pullup on port
   ///\brief enables weak pullup resistors on all pins in port object
   void pullup_enable()  override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->pullup_enable();
      }
   } 

   ///\brief disables pullup on port
   ///\brief disables weak pullup resistors on all pins in port object
   void pullup_disable()  override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->pullup_disable();
      }
   }  
};

//=======================port_out_from_pins_t===========================

///implementation of port_out_from_pins_t for remote Arduino Due
class port_out_from_pins_t : public due_remote_primitives::port_out{
private:
   static constexpr int max_pins = 16;
 
   uint_fast8_t _number_of_pins;  
 
   due_remote_primitives::pin_out * pins[ max_pins ]; 

public:

   /// Remote Arduino Due port_out_from_pins_t constructor
   /// 
   /// Constructor for a remote Arduino port_out_from_pins_t port
   ///
   /// Takes a set of max 16 pin_outs, and makes them adressable as a port

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

   ///\brief returns the number of pins in the port
   ///\details returns uint_fast8_t that is equal to amount of pins put into port
   uint_fast8_t number_of_pins() override{
      return _number_of_pins;
   }

   ///\brief writes given uint_fast16_t
   ///\brief writes given uint_fast16_t value onto the pins of the port, changes pin direction if necesarry
   void write( uint_fast16_t x ) override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->write((x & 0x01) != 0);
         x = x >> 1;
      }
   }      
   
   ///\brief flushes pins of the port
   ///\brief flushes most recent written values to pins of the port
   void flush() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->flush();
      }
   }
};

//==========================port_in_from_pins_t=========================

///implementation of port_in_from_pins_t for remote Arduino Due
class port_in_from_pins_t : public due_remote_primitives::port_in{
private:
   static constexpr int max_pins = 16;
 
   uint_fast8_t _number_of_pins;  
 
   due_remote_primitives::pin_in * pins[ max_pins ]; 

public:

   /// Remote Arduino Due port_in_from_pins_t constructor
   /// 
   /// Constructor for a remote Arduino port_in_from_pins_t port
   ///
   /// Takes a set of max 16 pin_ins, and makes them adressable as a port

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

   ///\brief returns the number of pins in the port
   ///\details returns uint_fast8_t that is equal to amount of pins put into port
   uint_fast8_t number_of_pins() override{
      return _number_of_pins;
   }
   
   ///\brief writes given uint_fast16_t
   ///\details writes given uint_fast16_t value onto the pins of the port, changes pin direction if necesarry
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
   
   ///\brief refreshes pins of the port
   ///\details refreshes values read on the pins of the port
   void refresh() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->refresh();
      }
   }

   ///\brief enables pullup on port
   ///\brief enables weak pullup resistors on all pins in port object
   void pullup_enable()  override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->pullup_enable();
      }
   } 

   ///\brief disables pullup on port
   ///\brief disables weak pullup resistors on all pins in port object
   void pullup_disable() override{
      for(uint_fast8_t i = 0; i < _number_of_pins; i++){
         pins[i]->pullup_disable();
      }
   }
};


//======================================================================
//
//                         input/output
//
//======================================================================

///get input from console screen
char uart_getc(){
   char character;
   std::cin >> character;
   return character;
}

///output character to console screen.
void uart_putc(char character){
   hwlib::cout << character;
}

};

// namespace due_remote
//======================================================================

#endif //HWLIB_ARDUINO_DUE_REMOTE_H