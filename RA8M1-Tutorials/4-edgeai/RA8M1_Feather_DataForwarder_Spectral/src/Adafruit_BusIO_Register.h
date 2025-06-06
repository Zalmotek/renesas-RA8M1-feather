#ifndef Adafruit_BusIO_Register_h
#define Adafruit_BusIO_Register_h

#define LSBFIRST 0

#include "Adafruit_I2CDevice.h"

Adafruit_I2CDevice i2c_dev;

typedef enum _Adafruit_BusIO_SPIRegType {
  ADDRBIT8_HIGH_TOREAD = 0,
  /*!<
   * ADDRBIT8_HIGH_TOREAD
   * When reading a register you must actually send the value 0x80 + register
   * address to the device. e.g. To read the register 0x0B the register value
   * 0x8B is sent and to write 0x0B is sent.
   */
  AD8_HIGH_TOREAD_AD7_HIGH_TOINC = 1,

  /*!<
   * ADDRBIT8_HIGH_TOWRITE
   * When writing to a register you must actually send the value 0x80 +
   * the register address to the device. e.g. To write to the register 0x19 the
   * register value 0x99 is sent and to read 0x19 is sent.
   */
  ADDRBIT8_HIGH_TOWRITE = 2,

  /*!<
   * ADDRESSED_OPCODE_LOWBIT_TO_WRITE
   * Used by the MCP23S series, we send 0x40 |'rd with the opcode
   * Then set the lowest bit to write
   */
  ADDRESSED_OPCODE_BIT0_LOW_TO_WRITE = 3,

} Adafruit_BusIO_SPIRegType;

/*!
 * @brief The class which defines a device register (a location to read/write
 * data from)
 */
class Adafruit_BusIO_Register {
public:
  Adafruit_BusIO_Register(uint16_t reg_addr,
                          uint8_t width = 1, uint8_t byteorder = LSBFIRST,
                          uint8_t address_width = 1);

  bool read(uint8_t *buffer, uint8_t len);
  bool read(uint8_t *value);
  bool read(uint16_t *value);
  uint32_t read(void);
  uint32_t readCached(void);
  bool write(uint8_t *buffer, uint8_t len);
  bool write(uint32_t value, uint8_t numbytes = 0);

  uint8_t width(void);

  void setWidth(uint8_t width);
  void setAddress(uint16_t address);
  void setAddressWidth(uint16_t address_width);

private:
  //Adafruit_BusIO_SPIRegType _spiregtype;
  uint16_t _address;
  uint8_t _width, _addrwidth, _byteorder;
  uint8_t _buffer[4]; // we won't support anything larger than uint32 for
                      // non-buffered read
  uint32_t _cached = 0;
};

/*!
 * @brief The class which defines a slice of bits from within a device register
 * (a location to read/write data from)
 */
class Adafruit_BusIO_RegisterBits {
public:
  Adafruit_BusIO_RegisterBits(Adafruit_BusIO_Register *reg, uint8_t bits,
                              uint8_t shift);
  bool write(uint32_t value);
  uint32_t read(void);

private:
  Adafruit_BusIO_Register *_register;
  uint8_t _bits, _shift;
};

/*!
 *    @brief  Create a register we access over an I2C Device (which defines the
 * bus and address)
 *    @param  i2cdevice The I2CDevice to use for underlying I2C access
 *    @param  reg_addr The address pointer value for the I2C/SMBus register, can
 * be 8 or 16 bits
 *    @param  width    The width of the register data itself, defaults to 1 byte
 *    @param  byteorder The byte order of the register (used when width is > 1),
 * defaults to LSBFIRST
 *    @param  address_width The width of the register address itself, defaults
 * to 1 byte
 */
Adafruit_BusIO_Register::Adafruit_BusIO_Register(uint16_t reg_addr,
                                                 uint8_t width,
                                                 uint8_t byteorder,
                                                 uint8_t address_width) {
  _addrwidth = address_width;
  _address = reg_addr;
  _byteorder = byteorder;
  _width = width;
}

/*!
 *    @brief  Write a buffer of data to the register location
 *    @param  buffer Pointer to data to write
 *    @param  len Number of bytes to write
 *    @return True on successful write (only really useful for I2C as SPI is
 * uncheckable)
 */
bool Adafruit_BusIO_Register::write(uint8_t *buffer, uint8_t len) {

  uint8_t addrbuffer[2] = {(uint8_t)(_address & 0xFF),
                           (uint8_t)(_address >> 8)};

  /*
  if (i2cdevice) {
    return i2cdevice->write(buffer, len, true, addrbuffer, _addrwidth);
  }
  */
  return i2c_dev.write(buffer, len, true, addrbuffer, _addrwidth);
  //return false;
}

/*!
 *    @brief  Write up to 4 bytes of data to the register location
 *    @param  value Data to write
 *    @param  numbytes How many bytes from 'value' to write
 *    @return True on successful write (only really useful for I2C as SPI is
 * uncheckable)
 */
bool Adafruit_BusIO_Register::write(uint32_t value, uint8_t numbytes) {
  if (numbytes == 0) {
    numbytes = _width;
  }
  if (numbytes > 4) {
    return false;
  }

  // store a copy
  _cached = value;

  for (int i = 0; i < numbytes; i++) {
    if (_byteorder == LSBFIRST) {
      _buffer[i] = value & 0xFF;
    } else {
      _buffer[numbytes - i - 1] = value & 0xFF;
    }
    value >>= 8;
  }

  return write(_buffer, numbytes);
}

/*!
 *    @brief  Read data from the register location. This does not do any error
 * checking!
 *    @return Returns 0xFFFFFFFF on failure, value otherwise
 */
uint32_t Adafruit_BusIO_Register::read(void) {
	if (!read(_buffer, _width)) {
    return -1;
  }

  uint32_t value = 0;

  for (int i = 0; i < _width; i++) {
    value <<= 8;
    if (_byteorder == LSBFIRST) {
      value |= _buffer[_width - i - 1];
    } else {
      value |= _buffer[i];
    }
  }

  return value;
}

/*!
 *    @brief  Read cached data from last time we wrote to this register
 *    @return Returns 0xFFFFFFFF on failure, value otherwise
 */
uint32_t Adafruit_BusIO_Register::readCached(void) { return _cached; }

/*!
 *    @brief  Read a buffer of data from the register location
 *    @param  buffer Pointer to data to read into
 *    @param  len Number of bytes to read
 *    @return True on successful write (only really useful for I2C as SPI is
 * uncheckable)
 */
bool Adafruit_BusIO_Register::read(uint8_t *buffer, uint8_t len) {
  uint8_t addrbuffer[2] = {(uint8_t)(_address & 0xFF),
                           (uint8_t)(_address >> 8)};

  /*
  if (_i2cdevice) {
    return _i2cdevice->write_then_read(addrbuffer, _addrwidth, buffer, len);
  }
  */
  return i2c_dev.write_then_read(addrbuffer, _addrwidth, buffer, len);
  //return false;
}

/*!
 *    @brief  Read 2 bytes of data from the register location
 *    @param  value Pointer to uint16_t variable to read into
 *    @return True on successful write (only really useful for I2C as SPI is
 * uncheckable)
 */
bool Adafruit_BusIO_Register::read(uint16_t *value) {
  if (!read(_buffer, 2)) {
    return false;
  }

  if (_byteorder == LSBFIRST) {
    *value = _buffer[1];
    *value <<= 8;
    *value |= _buffer[0];
  } else {
    *value = _buffer[0];
    *value <<= 8;
    *value |= _buffer[1];
  }
  return true;
}

/*!
 *    @brief  Read 1 byte of data from the register location
 *    @param  value Pointer to uint8_t variable to read into
 *    @return True on successful write (only really useful for I2C as SPI is
 * uncheckable)
 */
bool Adafruit_BusIO_Register::read(uint8_t *value) {
  if (!read(_buffer, 1)) {
    return false;
  }

  *value = _buffer[0];
  return true;
}

/*!
 *    @brief  Create a slice of the register that we can address without
 * touching other bits
 *    @param  reg The Adafruit_BusIO_Register which defines the bus/register
 *    @param  bits The number of bits wide we are slicing
 *    @param  shift The number of bits that our bit-slice is shifted from LSB
 */
Adafruit_BusIO_RegisterBits::Adafruit_BusIO_RegisterBits(
    Adafruit_BusIO_Register *reg, uint8_t bits, uint8_t shift) {
  _register = reg;
  _bits = bits;
  _shift = shift;
}

/*!
 *    @brief  Read 4 bytes of data from the register
 *    @return  data The 4 bytes to read
 */
uint32_t Adafruit_BusIO_RegisterBits::read(void) {
  uint32_t val = _register->read();
  val >>= _shift;
  return val & ((1 << (_bits)) - 1);
}

/*!
 *    @brief  Write 4 bytes of data to the register
 *    @param  data The 4 bytes to write
 *    @return True on successful write (only really useful for I2C as SPI is
 * uncheckable)
 */
bool Adafruit_BusIO_RegisterBits::write(uint32_t data) {
  uint32_t val = _register->read();

  // mask off the data before writing
  uint32_t mask = (1 << (_bits)) - 1;
  data &= mask;

  mask <<= _shift;
  val &= ~mask;          // remove the current data at that spot
  val |= data << _shift; // and add in the new data

  return _register->write(val, _register->width());
}

/*!
 *    @brief  The width of the register data, helpful for doing calculations
 *    @returns The data width used when initializing the register
 */
uint8_t Adafruit_BusIO_Register::width(void) { return _width; }

/*!
 *    @brief  Set the default width of data
 *    @param width the default width of data read from register
 */
void Adafruit_BusIO_Register::setWidth(uint8_t width) { _width = width; }

/*!
 *    @brief  Set register address
 *    @param address the address from register
 */
void Adafruit_BusIO_Register::setAddress(uint16_t address) {
  _address = address;
}

/*!
 *    @brief  Set the width of register address
 *    @param address_width the width for register address
 */
void Adafruit_BusIO_Register::setAddressWidth(uint16_t address_width) {
  _addrwidth = (uint8_t)address_width;
}

#endif // BusIO_Register_h
