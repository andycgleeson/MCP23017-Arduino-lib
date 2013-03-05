/*
  MCP20017.h - MCP20017 library for Arduino (v0.1).
  Copyright (C) 2013 Andy Gleeson (andy@rookeryforge.co.uk).  All rights reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/


// Data sheet for the MCP23017 available from the Microchip website www.microchip.com

#ifndef MCP23017_H
	#define MCP23017_H
#endif
     
#if (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include <Wire.h>


// Register addresses in IOCON.BANK = 0 mode, I dont handle any other mode in this library 

const uint8_t  IODIR=0x00;
const uint8_t  IODIRA=0x00;		// IO Direction Register Port A
const uint8_t  IODIRB=0x01;		// IO Direction Register Port B
								// 1 = Pin is configured as an input
								// 0 = Pin is configured as an output
								// Defaults to input

const uint8_t  IPOL=0x02;		
const uint8_t  IPOLA=0x02;			// Input polarity Register Port A
const uint8_t  IPOLB=0x03;			// Input polarity Register Port B
								// 1 = Input on pin is inverted in GPIO register 
								// 0 = Input on pin is the same in GPIO register 
								// Defaults to noninverting

const uint8_t  IPINTEN=0x04;
const uint8_t  IPINTENA=0x04;		// Interupt On Change Control Register Port A
const uint8_t  IPINTENB=0x05;		// Interupt On Change Control Register Port B
								// 1, Enable input pin for interupt on change event
								// 0, Disable input pin for interupt on change event
								// Defaults to disabled

const uint8_t  DEFVAL=0x06;	
const uint8_t  DEFVALA=0x06;		// Default Compare Register for Interupt on change Port A
const uint8_t  DEFVALB=0x07;		// Default Compare Register for Interupt on change Port B
								// If pin level opposite from register bit an interupt occurs
								// Defaults to 0
								// See datasheet INTCON and GPINTEN 
								

const uint8_t  INTCON=0x08;
const uint8_t  INTCONA=0x08;		// Interupt Control Register Port A
const uint8_t  INTCONB=0x09;		// Interupt Control Register Port B
								// Controls how pin value is compared for interupt on change
								// Defaults to 0
								// See datasheet INTCON and GPINTEN 

const uint8_t  IOCON=0x0A;									
const uint8_t  IOCONA=0x0A;		// I/O Expander Configuration Register Port A
const uint8_t  IOCONB=0x0B;		// I/O Expander Configuration Register Port B 
								// Shared registers controls various system parameters	
								// Defaults to all 0's		
								// See datasheet INTCON

const uint8_t  GPPU=0x0C;		
const uint8_t  GPPUA=0x0C;			// Pull up resistor Configuration register Port A
const uint8_t  GPPUB=0x0D;			// Pull up resistor Configuration register Port B
								// Enables 100k pull up resistor on corresponding port pin when in input mode
								// 1 = Pull up enabled
								// 0 = Pull up dissabled
								// Defaults to dissabled

const uint8_t  INTF=0x0E;
const uint8_t  INTFA=0x0E; 		// Interupt Flag Register Port A
const uint8_t  INTFB=0x0F;			// Interupt Flag Register Port A
								// A set bit indicates that the associated pin caused an interupt
								
const uint8_t  INTCAP=0x10;	
const uint8_t  INTCAPA=0x10;		// Interupt Capture Register Port A
const uint8_t  INTCAPB=0x11;		// Interupt Capture Register Port B
								// Captures the GPIO port value when the interupt occured

const uint8_t  GPIO=0x12;   
const uint8_t  GPIOA=0x12;         // Data Register Port A
const uint8_t  GPIOB=0x13;         // Data Register Port B
								// On input reflects value of the port
								// On write modifies the output latch register

const uint8_t  OLAT=0x014;	
const uint8_t  OLATA=0x014;		// Output Latch Register Port A
const uint8_t  OLATB=0x015;		// Output Latch Register Port B
								// Reflects the value on the output latch

// IOCON Bit designations

const uint8_t BANK=7; 				// Controls how the registers are addressed
     							// 1 = The registers associated with each port are separated into different banks
    							// 0 = The registers are in the same bank (addresses are sequential)
const uint8_t MIRROR=6;			// INT Pins Mirror bit
     							// 1 = The INT pins are internally connected
    							// 0 = The INT pins are not connected. INTA is associated with PortA and INTB is associated with PortB
const uint8_t SEQOP=5;				// Sequential Operation mode bit.
     							// 1 = Sequential operation disabled, address pointer does not increment.
    							// 0 = Sequential operation enabled, address pointer increments.
const uint8_t DISSLW=4;			// Slew Rate control bit for SDA output.
     							// 1 = Slew rate disabled.
    							// 0 = Slew rate enabled.
const uint8_t HAEN=3;				// Hardware Address Enable bit (MCP23S17 only).
     							// Address pins are always enabled on MCP23017.
    							// 1 = Enables the MCP23S17 address pins.
   								// 0 = Disables the MCP23S17 address pins.
const uint8_t ODR=2; 				// This bit configures the INT pin as an open-drain output.
     							// 1 = Open-drain output (overrides the INTPOL bit).
    							// 0 = Active driver output (INTPOL bit sets the polarity).
const uint8_t INTPOL=1;			// This bit sets the polarity of the INT output pin.
     							// 1 = Active-high.
    							// 0 = Active-low.


class MCP23017 {
	public:
        MCP23017();
        void begin(uint8_t addr);
		void writeRegister(uint8_t reg, uint8_t data);
		void writeRegisterPair(uint8_t reg, uint8_t dataA, uint8_t dataB);
		void setRegisterBit(uint8_t reg, uint8_t bit);
		void clearRegisterBit(uint8_t reg, uint8_t bit);
		uint8_t readRegisterBit(uint8_t reg, uint8_t bit);
		uint8_t readRegister(uint8_t reg);
		uint16_t readRegisterPair(uint8_t reg);
	private:
		uint8_t device_address;
    };
     


