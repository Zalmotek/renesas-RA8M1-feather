#ifndef AS7331_h
#define AS7331_h

#include "i2c_dev.h"

/*
 * https://www.mouser.com/catalog/specsheets/amsOsram_AS7331_DS001047_1-00.pdf
*/
// Configuration State registers
#define AS7331_OSR                      0x00
#define AS7331_AGEN                     0x02  // should be 0x21
#define AS7331_CREG1                    0x06
#define AS7331_CREG2                    0x07
#define AS7331_CREG3                    0x08
#define AS7331_BREAK                    0x09
#define AS7331_EDGES                    0x0A
#define AS7331_OPTREG                   0x0B

// Measurement State registers
#define AS7331_STATUS                   0x00
#define AS7331_TEMP                     0x01
#define AS7331_MRES1                    0x02
#define AS7331_MRES2                    0x03
#define AS7331_MRES3                    0x04
#define AS7331_OUTCONVL                 0x05
#define AS7331_OUTCONVH                 0x06


#define AS7331_ADDRESS  0x74  // if A0 = A1 = LOW

typedef enum {
  AS7331_CONT_MODE                = 0x00, // continuous mode
  AS7331_CMD_MODE                 = 0x01, // force mode, one-time measurement
  AS7331_SYNS_MODE                = 0x02,
  AS7331_SYND_MODE                = 0x03
} MMODE;


typedef enum  {
  AS7331_1024           = 0x00, // internal clock frequency, 1.024 MHz, etc
  AS7331_2048           = 0x01,
  AS7331_4096           = 0x02,
  AS7331_8192           = 0x03
} CCLK;


class AS7331
{
	public:
	  AS7331(I2Cdev* i2c_bus);
	  uint8_t getChipID();
	  void powerDown();
	  void powerUp();
	  void reset();
	  void setMeasurementMode();
	  void setConfigurationMode();
	  void init(uint8_t mmode, uint8_t cclk, uint8_t sb, uint8_t breakTime, uint8_t gain, uint8_t time);
	  void oneShot();
	  uint16_t readTempData();
	  uint16_t readUVAData();
	  uint16_t readUVBData();
	  uint16_t readUVCData();
	  void     readAllData(uint16_t * dest);
	  uint16_t getStatus();

	private:
	  I2Cdev* _i2c_bus;
};

AS7331::AS7331(I2Cdev* i2c_bus) {
	_i2c_bus = i2c_bus;
}


uint8_t AS7331::getChipID() {
	uint8_t c = _i2c_bus->readByte(AS7331_ADDRESS, AS7331_AGEN);
	return c;
}


void AS7331::powerDown() {
	uint8_t temp = _i2c_bus->readByte(AS7331_ADDRESS, AS7331_OSR);    // Read the raw data register
	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_OSR, temp & ~(0x40) ); // clear bit 6
}

void AS7331::powerUp() {
	uint8_t temp = _i2c_bus->readByte(AS7331_ADDRESS, AS7331_OSR);  // Read the raw data register
	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_OSR, temp | 0x40);   // set bit 6
}

void AS7331::reset() {
	uint8_t temp = _i2c_bus->readByte(AS7331_ADDRESS, AS7331_OSR);
	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_OSR, temp | 0x08); // set bit 3 for software reset the AS7331
}

void AS7331::setConfigurationMode() {
	uint8_t temp = _i2c_bus->readByte(AS7331_ADDRESS, AS7331_OSR);
	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_OSR, temp | 0x02); // set bit 1 for configuration mode
}

void AS7331::setMeasurementMode() {
	uint8_t temp = _i2c_bus->readByte(AS7331_ADDRESS, AS7331_OSR);
	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_OSR, temp | 0x83); // set bits 0,1 for measurement mode, start measurements
}

void AS7331::init(uint8_t mmode, uint8_t cclk, uint8_t sb, uint8_t breakTime, uint8_t gain, uint8_t time) {
//   set measurement mode (bits 6,7), standby on/off (bit 4)
//   and internal clk (bits 0,1); bit 3 determines ready interrupt configuration, 0 means push pull
//   1 means open drain
	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_CREG1, gain << 4 |  time ); //
	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_CREG3, mmode << 6 | sb << 4 | cclk ); //
   	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_BREAK, breakTime ); //
}

void AS7331::oneShot() {
	uint8_t temp = _i2c_bus->readByte(AS7331_ADDRESS, AS7331_OSR);
	_i2c_bus->writeByte(AS7331_ADDRESS, AS7331_OSR, temp | 0x80); // set bit 7 for forced one-time measurement
}

uint16_t AS7331::getStatus() {
	uint8_t rawData[2];  // 16-bit status register data stored here
	_i2c_bus->readBytes(AS7331_ADDRESS, AS7331_STATUS, 2, &rawData[0]);
	// first byte for OSR information and the second byte for STATUS information
	return (uint16_t)(((uint16_t)rawData[0]) << 8 | rawData[1]);
}

uint16_t AS7331::readTempData() {
	uint8_t rawData[2];  // 16-bit status register data stored here
	_i2c_bus->readBytes(AS7331_ADDRESS, AS7331_TEMP, 2, &rawData[0]);
	return (uint16_t)(((uint16_t)rawData[1]) << 8 | rawData[0]);
}

uint16_t AS7331::readUVAData() {
	uint8_t rawData[2];  // 16-bit status register data stored here
	_i2c_bus->readBytes(AS7331_ADDRESS, AS7331_MRES1, 2, &rawData[0]);
	return (uint16_t)(((uint16_t)rawData[1]) << 8 | rawData[0]);
}


uint16_t AS7331::readUVBData() {
	uint8_t rawData[2];  // 16-bit status register data stored here
	_i2c_bus->readBytes(AS7331_ADDRESS, AS7331_MRES2, 2, &rawData[0]);
	return (uint16_t)(((uint16_t)rawData[1]) << 8 | rawData[0]);
}

uint16_t AS7331::readUVCData() {
	uint8_t rawData[2];  // 16-bit status register data stored here
	_i2c_bus->readBytes(AS7331_ADDRESS, AS7331_MRES3, 2, &rawData[0]);
	return (uint16_t)(((uint16_t)rawData[1]) << 8 | rawData[0]);
}

void AS7331::readAllData(uint16_t * dest) {
	uint8_t rawData[8];  // 16-bit status register data stored here
	_i2c_bus->readBytes(AS7331_ADDRESS, AS7331_TEMP, 8, &rawData[0]);
	dest[0] =  (uint16_t)(((uint16_t)rawData[1]) << 8 | rawData[0]);
	dest[1]  =  (uint16_t)(((uint16_t)rawData[3]) << 8 | rawData[2]);
	dest[2]  =  (uint16_t)(((uint16_t)rawData[5]) << 8 | rawData[4]);
	dest[3]  =  (uint16_t)(((uint16_t)rawData[7]) << 8 | rawData[6]);
}

#endif
