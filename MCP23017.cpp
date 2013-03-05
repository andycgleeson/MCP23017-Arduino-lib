/*
  MCP20017.cpp - MCP20017 library for Arduino (v0.1).
  Copyright (C) 2013 Andy Gleeson (andy@rookeryforge.co.uk).  All rights reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/


#include "MCP23017.h" 

   
MCP23017::MCP23017(){}

void MCP23017::begin(uint8_t addr){
    device_address = addr;
	Wire.begin();	
	}

void MCP23017::writeRegister(uint8_t reg, uint8_t data){
	Wire.beginTransmission(device_address);
#if (ARDUINO >= 100)
	Wire.write(reg);    
  	Wire.write(data);  
#else
	Wire.send(reg);    
  	Wire.send(data);  
#endif
  	Wire.endTransmission();
	}

void MCP23017::writeRegisterPair(uint8_t reg, uint8_t dataA, uint8_t dataB){
	Wire.beginTransmission(device_address);
#if (ARDUINO >= 100)
	Wire.write(reg);    
  	Wire.write(dataA);
	Wire.write(dataB);  
#else
	Wire.send(reg);    
  	Wire.send(dataA);
	Wire.send(dataB);  
#endif
  	Wire.endTransmission();
	}


void MCP23017::setRegisterBit(uint8_t reg, uint8_t bit){
	// Set one bit in a MCP23017 register	
	uint8_t regbuf = readRegister(reg);
	bitSet(regbuf, bit);
	writeRegister(reg, regbuf); 
}

void MCP23017::clearRegisterBit(uint8_t reg, uint8_t bit){
	// Clear one bit in a MCP23017 register
	uint8_t regbuf = readRegister(reg);
	bitClear(regbuf, bit);
	writeRegister(reg, regbuf); 
}

uint8_t MCP23017::readRegisterBit(uint8_t reg, uint8_t bit){
	// Read one bit from a MCP23017 register
	uint8_t regbuf = readRegister(reg);
	bitRead(regbuf, bit);
	return regbuf;
}

uint8_t MCP23017::readRegister(uint8_t reg){
	uint8_t data;	
	Wire.beginTransmission(device_address);
#if (ARDUINO >= 100)
 	Wire.write(reg); 					// set MCP23017 memory pointer to register
#else
	Wire.send(reg);
#endif
 	Wire.endTransmission();
 	
	Wire.requestFrom(device_address, (uint8_t) 1); // request one uint8_t of data 
#if (ARDUINO >= 100)
 	data = Wire.read();
#else
	data = Wire.receive();
#endif
	return data;
    };

uint16_t MCP23017::readRegisterPair(uint8_t reg){
	uint16_t data;	

Wire.beginTransmission(device_address);
#if (ARDUINO >= 100)
 	Wire.write(reg); 					// set MCP23017 memory pointer to register
#else
	Wire.send(reg);
#endif
 	Wire.endTransmission();
	
	Wire.beginTransmission(device_address);
 	Wire.requestFrom(device_address, (uint8_t) 2); // request two uint8_ts of data 
#if (ARDUINO >= 100)
 	data = Wire.read(); 
  	data <<= 8;
  	data |= Wire.read(); 
#else
	data = Wire.receive(); 
  	data <<= 8;
  	data |= Wire.receive(); 
#endif
	Wire.endTransmission();

	return data;
    };



