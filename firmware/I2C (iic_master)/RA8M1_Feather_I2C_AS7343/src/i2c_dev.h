#ifndef _I2CDEV_H_
#define _I2CDEV_H_

#include "Wire.h"

class I2Cdev {
    public:
                                        I2Cdev();
                                        ~I2Cdev();                                                                                                                     // Class destructor for durable instances
         uint8_t                        readByte(uint8_t address, uint8_t subAddress);
         uint8_t                        readByte16(uint8_t devAddr, uint16_t regAddr);
         void                           readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);
         void                           readBytes16(uint8_t devAddr, uint16_t regAddr, uint8_t count, uint8_t * dest);
         void                           writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
         void                           writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t count, uint8_t *dest);
         void                           I2Cscan();                                                                                                                     // Class constructor argument
};

I2Cdev::I2Cdev()                                                                                                             // Class constructor
{
}

I2Cdev::~I2Cdev()                                                                                                                            // Class destructor
{
}

/**
* @fn: readByte(uint8_t address, uint8_t subAddress)
*
* @brief: Read one byte from an I2C device
*
* @params: I2C slave device address, Register subAddress
* @returns: unsigned short read
*/
uint8_t I2Cdev::readByte(uint8_t address, uint8_t subAddress)
{
  uint8_t data = 0;                             // `data` will store the register data
  beginTransmission(address);         // Initialize the Tx buffer
  write(subAddress);                  // Put slave register address in Tx buffer
  endTransmission(true);             // Send the Tx buffer, but send a restart to keep connection alive
  requestFrom(address, 1);            // Read one byte from slave register address
  data = read();                      // Fill Rx buffer with result
  return data;                                  // Return data read from slave register

}


/**
* @fn: readByte16(uint8_t address, uint16_t subAddress)
*
* @brief: Read one byte from an I2C device with 16-bit register addresses
*
* @params: I2C slave device address, Register subAddress
* @returns: unsigned short read
*/
uint8_t I2Cdev::readByte16(uint8_t devAddr, uint16_t regAddr)
{
  uint8_t data = 0;                             // `data` will store the register data
  beginTransmission(devAddr);         // Initialize the Tx buffer
  write((regAddr >> 8) & 0xFF);       // Put MSB of 16-bit slave register address in Tx buffer
  write(regAddr & 0xFF);              // Put LSB of 16-bit slave register address in Tx buffer
  endTransmission(true);             // Send the Tx buffer, but send a restart to keep connection alive
  requestFrom(devAddr, 1);            // Read one byte from slave register address
  data = read();                      // Fill Rx buffer with result
  return data;                                  // Return data read from slave register
}


/**
* @fn: readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
*
* @brief: Read multiple bytes from an I2C device
*
* @params: I2C slave device address, Register subAddress, number of btes to be read, aray to store the read data
* @returns: void
*/
void I2Cdev::readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
{
  beginTransmission(address);   // Initialize the Tx buffer
  write(subAddress);            // Put slave register address in Tx buffer
  endTransmission(true);       // Send the Tx buffer, but send a restart to keep connection alive
  uint8_t i = 0;
  requestFrom(address, count);  // Read bytes from slave register address
  while (available()) {
        dest[i++] = read(); }   // Put read results in the Rx buffer
}


/**
* @fn: readBytes16(uint8_t address, uint16_t subAddress, uint8_t count, uint8_t * dest)
*
* @brief: Read multiple bytes from an I2C device with 16-bit address registers
*
* @params: I2C slave device address, Register subAddress, number of btes to be read, aray to store the read data
* @returns: void
*/
void I2Cdev::readBytes16(uint8_t devAddr, uint16_t regAddr, uint8_t count, uint8_t * dest)
{
  beginTransmission(devAddr);    // Initialize the Tx buffer
  write((regAddr >> 8) & 0xFF); // Put MSB of 16-bit slave register address in Tx buffer
  write(regAddr & 0xFF);         // Put LSB of 16-bit slave register address in Tx buffer
  endTransmission(true);        // Send the Tx buffer, but send a restart to keep connection alive
  uint8_t i = 0;
  requestFrom(devAddr, count);   // Read bytes from slave register address
  while (available()) {
        dest[i++] = read(); }    // Put read results in the Rx buffer
}

/**
* @fn: writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
*
* @brief: Write one byte to an I2C device
*
* @params: I2C slave device address, Register subAddress, data to be written
* @returns: void
*/
void I2Cdev::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
  beginTransmission(devAddr);  // Initialize the Tx buffer
  write(regAddr);           // Put slave register address in Tx buffer
  write(data);                 // Put data in Tx buffer
  endTransmission(false);           // Send the Tx buffer
}


/**
* @fn: writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t data)
*
* @brief: Write multiple bytes to an I2C device
*
* @params: I2C slave device address, Register subAddress, byte count, data array to be written
* @returns: void
*/
void I2Cdev::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t count, uint8_t *dest)
{
  uint8_t temp[1 + count];
  temp[0] = regAddr;
  for (uint8_t ii = 0; ii < count; ii++)
  {
    temp[ii + 1] = dest[ii];
  }
  beginTransmission(devAddr);  // Initialize the Tx buffer
  for (uint8_t jj = 0; jj < count + 1; jj++) {
	  write(temp[jj]);            // Put data in Tx buffer
  }
  endTransmission(false);           // Send the Tx buffer
}

#endif //_I2CDEV_H_

