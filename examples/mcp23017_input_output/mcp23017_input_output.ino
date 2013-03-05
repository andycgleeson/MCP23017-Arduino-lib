// With momentary switches attached between bank A pins and ground this example
// works as a sort of 7 bit latching register. a low on any of the bank A pins except 
// pin 7 raises the corresponding pin on bank B. A low on bank A pin 7 resets bank 8 to
// all zeros. Can't think why this would be useful but it does demonstrate some of the 
// library functions.


#include <Wire.h>;
#include "MCP23017.h";

MCP23017 mcp;   // Create an instance of the MCP23017 class

void setup(){ 
  mcp = MCP23017();
  
  mcp.begin(0x20);  // Set the address of MCP23017 we are using
  
  mcp.writeRegister(IODIRA, 0xff);   // set bank A to input
  mcp.writeRegister(GPPUA, 0xff);    // enable pullup resisters on bank A
  mcp.writeRegister(IPOLA, 0xff);    // invert the polarity of bits on bank A
                                     // so that when we ground an input pin we get a 1
                                     // in the register
                                     

  mcp.writeRegister(IODIRB, 0x00);   // set bank B to output
  
  Serial.begin(9600);

}


void loop(){

  byte bank_a_data;
  byte bank_b_data;
  byte reset = 0;

  bank_a_data = mcp.readRegister(GPIOA);  // Read in value on bankA
  reset = mcp.readRegisterBit(GPIOA, 7);  // We can also read just 1 bit

  bank_b_data = mcp.readRegister(GPIOB);  // Read in value on bankB from it's output latch
                                      

  if (reset == 1) {                       // Got a reset clear GPIOB 
    reset = 0;
    mcp.writeRegister(GPIOB, 0x00);
    Serial.println("Reset");
  }
  else {                                  // or bank A with bank b and write back to bank A
    bank_b_data = bank_a_data | bank_b_data; 
    mcp.writeRegister(GPIOB, bank_b_data);
  }
  
  Serial.print("GPIOA ");
  Serial.print(bank_a_data, BIN);
  Serial.print(" GPIOB ");
  Serial.println(bank_b_data, BIN);
  
  delay(300);                             // Delay a bit so we can see whats happening

}


