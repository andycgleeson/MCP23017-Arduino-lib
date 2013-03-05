// interrupt example, use switches to ground, one switch from any pin of each port will do.

#include <Wire.h>;
#include "MCP23017.h";


MCP23017 mcp;

boolean intOccured = 0;


void setup(){ 
intOccured = 0;
mcp = MCP23017();
mcp.begin(0x20);
mcp.writeRegisterPair(IODIR, 0xff, 0xff);     // set both banks to input
mcp.writeRegisterPair(GPPU, 0xff, 0xff);      // enable pull up resistors so that we can use a simple switch
mcp.setRegisterBit(IOCON, MIRROR);            // set interrupt mirroring so that we can use just one interrupt line 
mcp.writeRegisterPair(IPINTEN, 0xff, 0xff);   // enable interrupts on all pins

attachInterrupt(0,interruptHandler,FALLING);  // attach our interupt handler, in this case to int 0 digital pin 2 on the UNO 

Serial.begin(9600);

}


void loop(){

  if (intOccured == 1){  // An interupt has occured better do something with it
    byte interruptFlagsA = mcp.readRegister(INTFA);              // Tells us which pin caused the interrupt
    byte interruptFlagsB = mcp.readRegister(INTFB);   
    byte interruptCaptureRegisterA = mcp.readRegister(INTCAPA);  // Contains GPIO data copied at the point the interrupt occured
    byte interruptCaptureRegisterB = mcp.readRegister(INTCAPB);  // Reading this register clears the interupt condition
    Serial.print("Interrupt Flag registers A=");
    Serial.print(interruptFlagsA, BIN);
    Serial.print(" B=");
    Serial.print(interruptFlagsB, BIN);
    Serial.print(" Capture registers A=");
    Serial.print(interruptCaptureRegisterA, BIN);
    Serial.print(" B=");
    Serial.println(interruptCaptureRegisterB, BIN);
    intOccured = 0;
  }
}



void interruptHandler(){  // Just set a flag, we don't want to spend time here
  intOccured = 1;
}
