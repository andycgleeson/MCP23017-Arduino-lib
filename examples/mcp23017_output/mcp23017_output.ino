#include <Wire.h>;
#include "MCP23017.h";

MCP23017 mcp;   // Create an instance of the MCP23017 class

void setup(){ 
mcp = MCP23017();
mcp.begin(0x20);  // Set the address of MCP23017 we are using*
mcp.writeRegisterPair(IODIR, 0x00, 0x00);   // set both banks to output

}


void loop(){

// set and rest all bits of each bank alternately
// connect an led between one bit of each bank and ground via a suitable reistor
// they should flash alternately.

mcp.writeRegisterPair(GPIO, 0xff, 0x00);
delay(400);
mcp.writeRegisterPair(GPIO, 0x00, 0xff);
delay(400);

// We could have written this using the writeRegister method thus:

mcp.writeRegister(GPIOA, 0xff);
mcp.writeRegister(GPIOB, 0x00);
delay(400);
mcp.writeRegister(GPIOA, 0x00);
mcp.writeRegister(GPIOB, 0xff0);
delay(400);


}

// *addresses consist of the base address 0x20 which is fixed,
// to which is added the value set on pins A0,A1 and A2 giving
// an address range of 0x20 to 0x27. in the example the address
// of 0x20 is obtained by taking all the address pins to ground 
