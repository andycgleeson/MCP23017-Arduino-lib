MCP23017 library for Arduino

This is a lightweight library for controlling the Microchip MCP23017 Port expander chip on the Arduino platform

To download click on the "Downloads" link in the upper right, click "Download as zip", and get a zip file.  Unzip it and rename the directory mcp23017_Arduino_library to MPC23017 place the directory in your arduino-x.x.x/libraries directory (where x.x.x is the version of Arduino you are running) and start or restart the Arduino IDE.

Library functions

begin(device-address);
writeRegister(reg-address, data);
writeRegisterPair(reg-address, dataA, dataB);
setRegisterBit(reg-address, bit);
clearRegisterBit(reg-address, bit);
readRegisterBit(reg-address, bit);
readRegister(reg-address);
readRegisterPair(reg-address);

There are a few examples showing usage of the library.

A datasheet for the MCP23017 chip is available on the Microchip website at www.microchip.com you will need this for anything apart from very basic usage of the chip.

Comments, ideas for improvement/extension welcome.


