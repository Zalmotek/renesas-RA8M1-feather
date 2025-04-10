/*!
 *  @file AMS_OSRAM_AS7343.h

 *  @mainpage AMS OSRAM AS7343 14-Channel Spectral Sensor
 *
 *  @section intro_sec Introduction
 *
 * 	I2C Driver for the Library for the AS7343 14-Channel Spectral Sensor
 *
 * 	This is a library for the Adafruit AS7343 breakout:
 * 	https://www.adafruit.com/product/4698
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section dependencies Dependencies
 *  This library depends on the Adafruit BusIO library
 *
 *  @section author Author
 *
 *  Bryan Siepert for Adafruit Industries
 *
 * 	@section license License
 *
 * 	BSD (see license.txt)
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

/*
  This library is adapted from an example with the following Copyright and
  Warranty:

  The main idea is to get fimilar with the
  register configuration. This code helps to learn basic settings and procedure
  to read out raw values with different SMUX configuration. Also defined the
  procedure to set the default flicker detection for 100 and 120 Hz.

  Written by Sijo John @ ams AG, Application Support in October, 2018

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

#ifndef _AMS_OSRAM_AS7343_H
#define _AMS_OSRAM_AS7343_H

#include "Adafruit_BusIO_Register.h"

#define AS7343_I2CADDR_DEFAULT 0x39 ///< AS7343 default i2c address
#define AS7343_CHIP_ID 0x81         ///< AS7343 default device id from datasheet

#define AS7343_WHOAMI 0x5A ///< Chip ID register

#define AS7343_ASTATUS 0x60     ///< AS7343_ASTATUS (unused)
#define AS7343_CH0_DATA_L_ 0x61 ///< AS7343_CH0_DATA_L (unused)
#define AS7343_CH0_DATA_H_ 0x62 ///< AS7343_CH0_DATA_H (unused)
#define AS7343_ITIME_L 0x63     ///< AS7343_ITIME_L (unused)
#define AS7343_ITIME_M 0x64     ///< AS7343_ITIME_M (unused)
#define AS7343_ITIME_H 0x65     ///< AS7343_ITIME_H (unused)
#define AS7343_CONFIG 0x70 ///< Enables LED control and sets light sensing mode
#define AS7343_STAT 0x71   ///< AS7343_STAT (unused)
#define AS7343_EDGE 0x72   ///< AS7343_EDGE (unused)
#define AS7343_GPIO 0x73   ///< Connects photo diode to GPIO or INT pins
#define AS7343_LED 0xCD    ///< LED Register; Enables and sets current limit
#define AS7343_ENABLE                                                          \
  0x80 ///< Main enable register. Controls SMUX, Flicker Detection, Spectral
       ///< Measurements and Power
#define AS7343_ATIME 0x81       ///< Sets ADC integration step count
#define AS7343_WTIME 0x83       ///< AS7343_WTIME (unused)
#define AS7343_SP_LOW_TH_L 0x84 ///< Spectral measurement Low Threshold low byte
#define AS7343_SP_LOW_TH_H                                                     \
  0x85 ///< Spectral measurement Low Threshold high byte
#define AS7343_SP_HIGH_TH_L                                                    \
  0x86 ///< Spectral measurement High Threshold low byte
#define AS7343_SP_HIGH_TH_H                                                    \
  0x87                    ///< Spectral measurement High Threshold low byte
#define AS7343_AUXID 0x58 ///< AS7343_AUXID (unused)
#define AS7343_REVID 0x59 ///< AS7343_REVID (unused)
#define AS7343_ID 0x92    ///< AS7343_ID (unused)
#define AS7343_STATUS                                                          \
  0x93 ///< Interrupt status registers. Indicates the occourance of an interrupt
#define AS7343_ASTATUS_ 0x94   ///< AS7343_ASTATUS, same as 0x60 (unused)
#define AS7343_CH0_DATA_L 0x95 ///< ADC Channel Data
#define AS7343_CH0_DATA_H 0x96 ///< ADC Channel Data
#define AS7343_CH1_DATA_L 0x97 ///< ADC Channel Data
#define AS7343_CH1_DATA_H 0x98 ///< ADC Channel Data
#define AS7343_CH2_DATA_L 0x99 ///< ADC Channel Data
#define AS7343_CH2_DATA_H 0x9A ///< ADC Channel Data
#define AS7343_CH3_DATA_L 0x9B ///< ADC Channel Data
#define AS7343_CH3_DATA_H 0x9C ///< ADC Channel Data
#define AS7343_CH4_DATA_L 0x9D ///< ADC Channel Data
#define AS7343_CH4_DATA_H 0x9E ///< ADC Channel Data
#define AS7343_CH5_DATA_L 0x9F ///< ADC Channel Data
#define AS7343_CH5_DATA_H 0xA0 ///< ADC Channel Data
#define AS7343_CH6_DATA_L 0xA1 ///< ADC Channel Data
#define AS7343_CH6_DATA_H 0xA2 ///< ADC Channel Data
#define AS7343_CH7_DATA_L 0xA3 ///< ADC Channel Data
#define AS7343_CH7_DATA_H 0xA4 ///< ADC Channel Data
#define AS7343_CH8_DATA_L 0xA5 ///< ADC Channel Data
#define AS7343_CH8_DATA_H 0xA6 ///< ADC Channel Data
#define AS7343_CH9_DATA_L 0xA7 ///< ADC Channel Data
#define AS7343_CH9_DATA_H 0xA8 ///< ADC Channel Data
#define AS7343_CH10_DATA_L 0xA9 ///< ADC Channel Data
#define AS7343_CH10_DATA_H 0xAA ///< ADC Channel Data
#define AS7343_CH11_DATA_L 0xAB ///< ADC Channel Data
#define AS7343_CH11_DATA_H 0xAC ///< ADC Channel Data
#define AS7343_CH12_DATA_L 0xAD ///< ADC Channel Data
#define AS7343_CH12_DATA_H 0xAE ///< ADC Channel Data
#define AS7343_CH13_DATA_L 0xAF ///< ADC Channel Data
#define AS7343_CH13_DATA_H 0xB0 ///< ADC Channel Data
#define AS7343_CH14_DATA_L 0xB1 ///< ADC Channel Data
#define AS7343_CH14_DATA_H 0xB2 ///< ADC Channel Data
#define AS7343_CH15_DATA_L 0xB3 ///< ADC Channel Data
#define AS7343_CH15_DATA_H 0xB4 ///< ADC Channel Data
#define AS7343_CH16_DATA_L 0xB5 ///< ADC Channel Data
#define AS7343_CH16_DATA_H 0xB6 ///< ADC Channel Data
#define AS7343_CH17_DATA_L 0xB7 ///< ADC Channel Data
#define AS7343_CH17_DATA_H 0xB8 ///< ADC Channel Data

#define AS7343_STATUS2 0x90 ///< Measurement status flags; saturation, validity
#define AS7343_STATUS3                                                         \
  0x91 ///< Spectral interrupt source, high or low threshold
#define AS7343_STATUS5 0xBB ///< AS7343_STATUS5 (unused)
#define AS7343_STATUS4 0xBC ///< AS7343_STATUS6 (unused)
#define AS7343_CFG0                                                            \
  0xBF ///< Sets Low power mode, Register bank, and Trigger lengthening
#define AS7343_CFG1 0xC6 ///< Controls ADC Gain
#define AS7343_CFG3 0xC7 ///< AS7343_CFG3 (unused)
#define AS7343_CFG6 0xF5 ///< Used to configure Smux
#define AS7343_CFG8 0xC9 ///< AS7343_CFG8 (unused)
#define AS7343_CFG9                                                            \
  0xCA ///< Enables flicker detection and smux command completion system
       ///< interrupts
#define AS7343_CFG10 0x65 ///< AS7343_CFG10 (unused)
#define AS7343_CFG12                                                           \
  0x66 ///< Spectral threshold channel for interrupts, persistence and auto-gain
#define AS7343_CFG20 0xD6 //< FIFO and auto SMUX
#define AS7343_PERS                                                            \
  0xCF ///< Number of measurement cycles outside thresholds to trigger an
       ///< interupt
#define AS7343_GPIO2                                                           \
  0x6B ///< GPIO Settings and status: polarity, direction, sets output, reads
       ///< input
#define AS7343_ASTEP_L 0xD4      ///< Integration step size ow byte
#define AS7343_ASTEP_H 0xD5      ///< Integration step size high byte
#define AS7343_AGC_GAIN_MAX 0xD7 ///< AS7343_AGC_GAIN_MAX (unused)
#define AS7343_AZ_CONFIG 0xDE    ///< AS7343_AZ_CONFIG (unused)
#define AS7343_FD_TIME1 0xE0 ///< Flicker detection integration time low byte
#define AS7343_FD_TIME2 0xE2 ///< Flicker detection gain and high nibble
#define AS7343_FD_CFG0 0xDF  ///< AS7343_FD_CFG0 (unused)
#define AS7343_FD_STATUS                                                       \
  0xE3 ///< Flicker detection status; measurement valid, saturation, flicker
       ///< type
#define AS7343_INTENAB 0xF9  ///< Enables individual interrupt types
#define AS7343_CONTROL 0xFA  ///< Auto-zero, fifo clear, clear SAI active
#define AS7343_FIFO_MAP 0xFC ///< AS7343_FIFO_MAP (unused)
#define AS7343_FIFO_LVL 0xFD ///< AS7343_FIFO_LVL (unused)
#define AS7343_FDATA_L 0xFE  ///< AS7343_FDATA_L (unused)
#define AS7343_FDATA_H 0xFF  ///< AS7343_FDATA_H (unused)

#define AS7343_SPECTRAL_INT_HIGH_MSK                                           \
  0b00100000 ///< bitmask to check for a high threshold interrupt
#define AS7343_SPECTRAL_INT_LOW_MSK                                            \
  0b00010000 ///< bitmask to check for a low threshold interrupt


/**
 * @brief Allowable gain multipliers for `setGain`
 *
 */
typedef enum {
  AS7343_GAIN_0_5X,
  AS7343_GAIN_1X,
  AS7343_GAIN_2X,
  AS7343_GAIN_4X,
  AS7343_GAIN_8X,
  AS7343_GAIN_16X,
  AS7343_GAIN_32X,
  AS7343_GAIN_64X,
  AS7343_GAIN_128X,
  AS7343_GAIN_256X,
  AS7343_GAIN_512X,
  AS7343_GAIN_1024X,
  AS7343_GAIN_2048X,
} AS7343_gain_t;

/**
 * @brief Available SMUX configuration commands
 *
 */
typedef enum {
  AS7343_SMUX_CMD_ROM_RESET, ///< ROM code initialization of SMUX
  AS7343_SMUX_CMD_READ,      ///< Read SMUX configuration to RAM from SMUX chain
  AS7343_SMUX_CMD_WRITE, ///< Write SMUX configuration from RAM to SMUX chain
} AS7343_smux_cmd_t;
/**
 * @brief ADC Channel specifiers for configuration
 *
 */
typedef enum {
  AS7343_ADC_CHANNEL_0,
  AS7343_ADC_CHANNEL_1,
  AS7343_ADC_CHANNEL_2,
  AS7343_ADC_CHANNEL_3,
  AS7343_ADC_CHANNEL_4,
  AS7343_ADC_CHANNEL_5,
} AS7343_adc_channel_t;
/**
 * @brief Spectral Channel specifiers for configuration and reading
 *
 */
typedef enum {
  AS7343_CHANNEL_450_FZ,
  AS7343_CHANNEL_555_FY,
  AS7343_CHANNEL_600_FXL,
  AS7343_CHANNEL_855_NIR,
  AS7343_CHANNEL_CLEAR_1,
  AS7343_CHANNEL_FD_1,
  AS7343_CHANNEL_425_F2,
  AS7343_CHANNEL_475_F3,
  AS7343_CHANNEL_515_F4,
  AS7343_CHANNEL_640_F6,
  AS7343_CHANNEL_CLEAR_0,
  AS7343_CHANNEL_FD_0,
  AS7343_CHANNEL_405_F1,
  AS7343_CHANNEL_550_F5,
  AS7343_CHANNEL_690_F7,
  AS7343_CHANNEL_745_F8,
  AS7343_CHANNEL_CLEAR,
  AS7343_CHANNEL_FD,
} AS7343_color_channel_t;

/**
 * @brief The number of measurement cycles with spectral data outside of a
 * threshold required to trigger an interrupt
 *
 */
typedef enum {
  AS7343_INT_COUNT_ALL, ///< 0
  AS7343_INT_COUNT_1,   ///< 1
  AS7343_INT_COUNT_2,   ///< 2
  AS7343_INT_COUNT_3,   ///< 3
  AS7343_INT_COUNT_5,   ///< 4
  AS7343_INT_COUNT_10,  ///< 5
  AS7343_INT_COUNT_15,  ///< 6
  AS7343_INT_COUNT_20,  ///< 7
  AS7343_INT_COUNT_25,  ///< 8
  AS7343_INT_COUNT_30,  ///< 9
  AS7343_INT_COUNT_35,  ///< 10
  AS7343_INT_COUNT_40,  ///< 11
  AS7343_INT_COUNT_45,  ///< 12
  AS7343_INT_COUNT_50,  ///< 13
  AS7343_INT_COUNT_55,  ///< 14
  AS7343_INT_COUNT_60,  ///< 15
} AS7343_int_cycle_count_t;

/**
 * @brief Pin directions to set how the GPIO pin is to be used
 *
 */
typedef enum {
  AS7343_GPIO_OUTPUT, ///< THhe GPIO pin is configured as an open drain output
  AS7343_GPIO_INPUT,  ///< The GPIO Pin is set as a high-impedence input
} AS7343_gpio_dir_t;

/**
 * @brief Wait states for async reading
 */
typedef enum {
  AS7343_WAITING_START, //
  AS7343_WAITING_LOW,   //
  AS7343_WAITING_HIGH,  //
  AS7343_WAITING_DONE,  //
} AS7343_waiting_t;

class AMS_OSRAM_AS7343;

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the AS7343 11-Channel Spectral Sensor
 */
class AMS_OSRAM_AS7343 {
public:
  AMS_OSRAM_AS7343();
  virtual ~AMS_OSRAM_AS7343();

  bool begin(uint8_t i2c_addr = AS7343_I2CADDR_DEFAULT,
             int32_t sensor_id = 0);

  bool setASTEP(uint16_t astep_value);
  bool setATIME(uint8_t atime_value);
  bool setGain(AS7343_gain_t gain_value);

  uint16_t getASTEP();
  uint8_t getATIME();
  AS7343_gain_t getGain();

  long getTINT();
  double toBasicCounts(uint16_t raw);

  bool readAllChannels(void);
  bool readAllChannels(uint16_t *readings_buffer);
  void delayForData(int waitTime = 0);
  uint16_t readChannel(AS7343_adc_channel_t channel);
  uint16_t getChannel(AS7343_color_channel_t channel);

  bool startReading(void);
  bool checkReadingProgress();
  bool getAllChannels(uint16_t *readings_buffer);

  uint16_t detectFlickerHz(void);

  void setup_F1F4_Clear_NIR(void);
  void setup_F5F8_Clear_NIR(void);

  void powerEnable(bool enable_power);
  bool enableSpectralMeasurement(bool enable_measurement);

  bool setHighThreshold(uint16_t high_threshold);
  bool setLowThreshold(uint16_t low_threshold);

  uint16_t getHighThreshold(void);
  uint16_t getLowThreshold(void);

  bool enableSpectralInterrupt(bool enable_int);
  bool enableSystemInterrupt(bool enable_int);

  bool setAPERS(AS7343_int_cycle_count_t cycle_count);
  bool setSpectralThresholdChannel(AS7343_adc_channel_t channel);

  uint8_t getInterruptStatus(void);
  bool clearInterruptStatus(void);

  bool spectralInterruptTriggered(void);
  uint8_t spectralInterruptSource(void);
  bool spectralLowTriggered(void);
  bool spectralHighTriggered(void);

  bool enableLED(bool enable_led);
  bool setLEDCurrent(uint16_t led_current_ma);
  uint16_t getLEDCurrent(void);

  void disableAll(void);

  bool getIsDataReady();
  bool setBank(bool low); // low true gives access to 0x60 to 0x74

  AS7343_gpio_dir_t getGPIODirection(void);
  bool setGPIODirection(AS7343_gpio_dir_t gpio_direction);
  bool getGPIOInverted(void);
  bool setGPIOInverted(bool gpio_inverted);
  bool getGPIOValue(void);
  bool setGPIOValue(bool);

  bool digitalSaturation(void);
  bool analogSaturation(void);
  bool clearDigitalSaturationStatus(void);
  bool clearAnalogSaturationStatus(void);

protected:
  virtual bool _init(int32_t sensor_id);
  uint8_t last_spectral_int_source =
      0; ///< The value of the last reading of the spectral interrupt source
         ///< register

  //Adafruit_I2CDevice *i2c_dev; ///< Pointer to I2C bus interface

private:
  bool enableSMUX(void);
  bool enableFlickerDetection(bool enable_fd);
  void FDConfig(void);
  int8_t getFlickerDetectStatus(void);
  bool setSMUXCommand(AS7343_smux_cmd_t command);
  void writeRegister(uint8_t addr, uint8_t val);
  void setSMUXLowChannels(bool f1_f4);
  uint16_t _channel_readings[18];
  AS7343_waiting_t _readingState;
};

/**
 * @brief Construct a new AMS_OSRAM_AS7343::AMS_OSRAM_AS7343 object
 *
 */
AMS_OSRAM_AS7343::AMS_OSRAM_AS7343(void) {
	_readingState = AS7343_WAITING_START;
}

/**
 * @brief Destroy the AMS_OSRAM_AS7343::AMS_OSRAM_AS7343 object
 *
 */
AMS_OSRAM_AS7343::~AMS_OSRAM_AS7343(void) {
  //   if (temp_sensor)
  //     delete temp_sensor;
  //   if (pressure_sensor)
  //     delete pressure_sensor;
}

/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @param  sensor_id
 *            The unique ID to differentiate the sensors from others
 *    @return True if initialization was successful, otherwise false.
 */
bool AMS_OSRAM_AS7343::begin(uint8_t i2c_address,
                            int32_t sensor_id) {
  /*
	if () {
    	delete i2c_dev; // remove old interface
  	  }
   */

	//i2c_dev = new Adafruit_I2CDevice(i2c_address);
	i2c_dev.set_address(i2c_address);

  if (!i2c_dev.begin()) {
    return false;
  }
  return _init(sensor_id);
}

/*!  @brief Initializer for post i2c/spi init
 *   @param sensor_id Optional unique ID for the sensor set
 *   @returns True if chip identified and initialized
 */
bool AMS_OSRAM_AS7343::_init(int32_t sensor_id) {

  // silence compiler warning - variable may be used in the future
  (void)sensor_id;

  // make sure we're talking to the right chip
  Adafruit_BusIO_Register chip_id_reg =
      Adafruit_BusIO_Register(AS7343_WHOAMI);
  setBank(true); //Access registers 0x20 to 0x7F
  uint8_t chip_id = (uint8_t)chip_id_reg.read();
  setBank(false); //Access to registers 0x80 and above (default)
  if (chip_id != AS7343_CHIP_ID) {
    return false;
  }

  powerEnable(true);

  Adafruit_BusIO_Register cfg20_reg =
      Adafruit_BusIO_Register(AS7343_CFG20);
  Adafruit_BusIO_RegisterBits auto_smux_bit =
      Adafruit_BusIO_RegisterBits(&cfg20_reg, 2, 5);
  if(!auto_smux_bit.write(3)) {
    return false;
  }

  return true;
}

/********************* EXAMPLE EXTRACTS **************/
// maybe return a typedef enum
/**
 * @brief Returns the flicker detection status
 *
 * @return int8_t
 */
int8_t AMS_OSRAM_AS7343::getFlickerDetectStatus(void) {
  Adafruit_BusIO_Register flicker_val =
      Adafruit_BusIO_Register(AS7343_FD_STATUS);
  return (int8_t)flicker_val.read();
}

/**
 * @brief Returns the ADC data for a given channel
 *
 * @param channel The ADC channel to read
 * @return uint16_t The measured data for the currently configured sensor
 */
uint16_t AMS_OSRAM_AS7343::readChannel(AS7343_adc_channel_t channel) {
  // each channel has two bytes, so offset by two for each next channel
  Adafruit_BusIO_Register channel_data_reg = Adafruit_BusIO_Register(
      (uint16_t)(AS7343_CH0_DATA_L + 2 * channel), 2, LSBFIRST);

  return (uint16_t)channel_data_reg.read();
}

/**
 * @brief Returns the reading data for the specified color channel
 *
 *  call `readAllChannels` before reading to update the stored readings
 *
 * @param channel The color sensor channel to read
 * @return uint16_t The measured data for the selected sensor channel
 */
uint16_t AMS_OSRAM_AS7343::getChannel(AS7343_color_channel_t channel) {
  return _channel_readings[channel];
}

/**
 * @brief fills the provided buffer with the current measurements for Spectral
 * channels F1-8, Clear and NIR
 *
 * @param readings_buffer Pointer to a buffer of length 10 or more to fill with
 * sensor data
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::readAllChannels(uint16_t *readings_buffer) {

  //enableSMUX();
  //clearAnalogSaturationStatus();
  //clearDigitalSaturationStatus();
  enableSpectralMeasurement(true); // Start integration
  delayForData(0);                 // I'll wait for you for all time

  Adafruit_BusIO_Register channel_data_reg =
      Adafruit_BusIO_Register(AS7343_CH0_DATA_L, 2);
  return channel_data_reg.read((uint8_t *)readings_buffer, 36);
}

/**
 * @brief starts the process of getting readings from all channels without using
 * delays
 *
 * @return true: success false: failure (a bit arbitrary)
 */
bool AMS_OSRAM_AS7343::startReading(void) {
  _readingState = AS7343_WAITING_START; // Start the measurement please
  checkReadingProgress();               // Call the check function to start it
  return true;
}

/**
 * @brief runs the process of getting readings from all channels without using
 * delays.  Should be called regularly (ie. in loop()) Need to call
 * startReading() to initialise the process Need to call getAllChannels() to
 * transfer the data into an external buffer
 *
 * @return true: reading is complete false: reading is incomplete (or failed)
 */
bool AMS_OSRAM_AS7343::checkReadingProgress() {
  if (_readingState == AS7343_WAITING_START) {
    setSMUXLowChannels(true);        // Configure SMUX to read low channels
    enableSpectralMeasurement(true); // Start integration
    _readingState = AS7343_WAITING_LOW;
    return false;
  }

  if (!getIsDataReady() || _readingState == AS7343_WAITING_DONE)
    return false;

  if (_readingState ==
      AS7343_WAITING_LOW) // Check of getIsDataRead() is already done
  {
    Adafruit_BusIO_Register channel_data_reg =
        Adafruit_BusIO_Register(AS7343_CH0_DATA_L, 2);

    // bool low_success = channel_data_reg.read((uint8_t *)_channel_readings,
    // 12);
    channel_data_reg.read((uint8_t *)_channel_readings, 12);

    setSMUXLowChannels(false);       // Configure SMUX to read high channels
    enableSpectralMeasurement(true); // Start integration
    _readingState = AS7343_WAITING_HIGH;
    return false;
  }

  if (_readingState ==
      AS7343_WAITING_HIGH) // Check of getIsDataRead() is already done
  {
    _readingState = AS7343_WAITING_DONE;
    Adafruit_BusIO_Register channel_data_reg =
        Adafruit_BusIO_Register(AS7343_CH0_DATA_L, 2);
    // return low_success &&			//low_success is lost since it
    // was last call
    channel_data_reg.read((uint8_t *)&_channel_readings[6], 12);
    return true;
  }

  return false;
}

/**
 * @brief transfer all the values from the private result buffer into one
 * nominated
 *
 * @param readings_buffer Pointer to a buffer of length 12 (THERE IS NO ERROR
 * CHECKING, YE BE WARNED!)
 *
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::getAllChannels(uint16_t *readings_buffer) {
  for (int i = 0; i < 12; i++)
    readings_buffer[i] = _channel_readings[i];
  return true;
}

/**
 * @brief Delay while waiting for data, with option to time out and recover
 *
 * @param waitTime the maximum amount of time to wait
 * @return none
 */
void AMS_OSRAM_AS7343::delayForData(int waitTime) {
  if (waitTime == 0) // Wait forever
  {
    while (!getIsDataReady()) {
    	R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    }
    return;
  }
  if (waitTime > 0) // Wait for that many milliseconds
  {
    uint32_t elapsedMillis = 0;
    while (!getIsDataReady() && elapsedMillis < (uint32_t)waitTime) {
    	R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
      elapsedMillis++;
    }
    return;
  }
  if (waitTime < 0) {
    // For future use?
    return;
  }
}

/**
 * @brief Take readings for F1-8, Clear and NIR and store them in a buffer
 *
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::readAllChannels(void) {
  return readAllChannels(_channel_readings);
}

void AMS_OSRAM_AS7343::setSMUXLowChannels(bool f1_f4) {
  enableSpectralMeasurement(false);
  setSMUXCommand(AS7343_SMUX_CMD_WRITE);
  if (f1_f4) {
    setup_F1F4_Clear_NIR();
  } else {
    setup_F5F8_Clear_NIR();
  }
  enableSMUX();
}

/**
 * @brief Sets the power state of the sensor
 *
 * @param enable_power true: on false: off
 */
void AMS_OSRAM_AS7343::powerEnable(bool enable_power) {
  Adafruit_BusIO_Register enable_reg =
      Adafruit_BusIO_Register(AS7343_ENABLE);
  Adafruit_BusIO_RegisterBits pon_en =
      Adafruit_BusIO_RegisterBits(&enable_reg, 1, 0);
  pon_en.write(enable_power);
}

/**
 * @brief Disable Spectral reading, flicker detection, and power
 *
 * */
void AMS_OSRAM_AS7343::disableAll(void) {
  Adafruit_BusIO_Register enable_reg =
      Adafruit_BusIO_Register(AS7343_ENABLE);

  enable_reg.write(0);
}

/**
 * @brief Enables measurement of spectral data
 *
 * @param enable_measurement true: enabled false: disabled
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::enableSpectralMeasurement(bool enable_measurement) {

  Adafruit_BusIO_Register enable_reg =
      Adafruit_BusIO_Register(AS7343_ENABLE);

  Adafruit_BusIO_RegisterBits spec_enable_bit =
      Adafruit_BusIO_RegisterBits(&enable_reg, 1, 1);
  return spec_enable_bit.write(enable_measurement);
}

bool AMS_OSRAM_AS7343::enableSMUX(void) {

  Adafruit_BusIO_Register enable_reg =
      Adafruit_BusIO_Register(AS7343_ENABLE);
  Adafruit_BusIO_RegisterBits smux_enable_bit =
      Adafruit_BusIO_RegisterBits(&enable_reg, 1, 4);
  bool success = smux_enable_bit.write(true);

  int timeOut = 1000; // Arbitrary value, but if it takes 1000 milliseconds then
                      // something is wrong
  int count = 0;
  while (smux_enable_bit.read() && count < timeOut) {
	  R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    count++;
  }
  if (count >= timeOut)
    return false;
  else
    return success;
}

bool AMS_OSRAM_AS7343::enableFlickerDetection(bool enable_fd) {

  Adafruit_BusIO_Register enable_reg =
      Adafruit_BusIO_Register(AS7343_ENABLE);
  Adafruit_BusIO_RegisterBits fd_enable_bit =
      Adafruit_BusIO_RegisterBits(&enable_reg, 1, 6);
  return fd_enable_bit.write(enable_fd);
}

/**
 * @brief Get the GPIO pin direction setting
 *
 * @return `AS7343_OUTPUT` or `AS7343_INPUT`
 */
AS7343_gpio_dir_t AMS_OSRAM_AS7343::getGPIODirection(void) {
  Adafruit_BusIO_Register gpio2_reg =
      Adafruit_BusIO_Register(AS7343_GPIO2);
  Adafruit_BusIO_RegisterBits gpio_input_enable =
      Adafruit_BusIO_RegisterBits(&gpio2_reg, 1, 2);

  return (AS7343_gpio_dir_t)gpio_input_enable.read();
}

/**
 * @brief Set the GPIO pin to be used as an input or output
 *
 * @param gpio_direction The IO direction to set
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setGPIODirection(AS7343_gpio_dir_t gpio_direction) {
  Adafruit_BusIO_Register gpio2_reg =
      Adafruit_BusIO_Register(AS7343_GPIO2);
  Adafruit_BusIO_RegisterBits gpio_input_enable =
      Adafruit_BusIO_RegisterBits(&gpio2_reg, 1, 2);

  return gpio_input_enable.write(gpio_direction);
}

/**
 * @brief Get the output inversion setting for the GPIO pin
 *
 * @return true: GPIO output inverted false: GPIO output normal
 */
bool AMS_OSRAM_AS7343::getGPIOInverted(void) {
  Adafruit_BusIO_Register gpio2_reg =
      Adafruit_BusIO_Register(AS7343_GPIO2);
  Adafruit_BusIO_RegisterBits gpio_output_inverted_bit =
      Adafruit_BusIO_RegisterBits(&gpio2_reg, 1, 3);

  return gpio_output_inverted_bit.read();
}

/**
 * @brief Invert the logic of then GPIO pin when used as an output
 *
 * @param gpio_inverted **When true** setting the gpio value to **true will
 * connect** the GPIO pin to ground. When set to **false**, setting the GPIO pin
 * value to **true will disconnect** the GPIO pin from ground
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setGPIOInverted(bool gpio_inverted) {
  Adafruit_BusIO_Register gpio2_reg =
      Adafruit_BusIO_Register(AS7343_GPIO2);
  Adafruit_BusIO_RegisterBits gpio_output_inverted_bit =
      Adafruit_BusIO_RegisterBits(&gpio2_reg, 1, 3);

  return gpio_output_inverted_bit.write(gpio_inverted);
}

/**
 * @brief Read the digital level of the GPIO pin, high or low
 *
 * @return true: GPIO pin level is high false: GPIO pin level is low
 */
bool AMS_OSRAM_AS7343::getGPIOValue(void) {
  Adafruit_BusIO_Register gpio2_reg =
      Adafruit_BusIO_Register(AS7343_GPIO2);
  Adafruit_BusIO_RegisterBits gpio_input_value_bit =
      Adafruit_BusIO_RegisterBits(&gpio2_reg, 1, 0);

  return gpio_input_value_bit.read();
}

/**
 * @brief Set the digital level of the GPIO pin, high or low
 *
 * @param gpio_high The GPIO level to set. Set to true to disconnect the pin
 * from ground. Set to false to connect the gpio pin to ground. This can be used
 * to connect the cathode of an LED to ground to turn it on.
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setGPIOValue(bool gpio_high) {
  Adafruit_BusIO_Register gpio2_reg =
      Adafruit_BusIO_Register(AS7343_GPIO2);
  Adafruit_BusIO_RegisterBits gpio_output_value_bit =
      Adafruit_BusIO_RegisterBits(&gpio2_reg, 1, 1);

  return gpio_output_value_bit.write(gpio_high);
}

bool AMS_OSRAM_AS7343::setSMUXCommand(AS7343_smux_cmd_t command) {
  Adafruit_BusIO_Register cfg6_reg =
      Adafruit_BusIO_Register(AS7343_CFG6);
  Adafruit_BusIO_RegisterBits smux_command_bits =
      Adafruit_BusIO_RegisterBits(&cfg6_reg, 2, 3);

  return smux_command_bits.write(command);
}

/**
 * @brief Enable control of an attached LED on the LDR pin
 *
 * @param enable_led true: LED enabled false: LED disabled
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::enableLED(bool enable_led) {
  Adafruit_BusIO_Register config_reg =
      Adafruit_BusIO_Register(AS7343_CONFIG);
  // Enables control of the LED via the LDR pin
  // 1=control enabled 0 = control disabled
  Adafruit_BusIO_RegisterBits led_sel_bit =
      Adafruit_BusIO_RegisterBits(&config_reg, 1, 3);

  Adafruit_BusIO_Register led_reg =
      Adafruit_BusIO_Register(AS7343_LED);
  // turns the LED on or off
  Adafruit_BusIO_RegisterBits led_act_bit =
      Adafruit_BusIO_RegisterBits(&led_reg, 1, 7);

  setBank(true); // Access registers 0x20 to 0x7F
  bool result = led_sel_bit.write(enable_led) && led_act_bit.write(enable_led);
  setBank(false); // Access registers 0x80 and above (default)
  return result;
}

/**
 * @brief Set the current limit for the LED
 *
 * @param led_current_ma the value to set in milliamps. With a minimum of 4. Any
 * amount under 4 will be rounded up to 4
 *
 * Range is 4mA to 258mA
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setLEDCurrent(uint16_t led_current_ma) {
  // check within permissible range
  if (led_current_ma > 258) {
    return false;
  }
  if (led_current_ma < 4) {
    led_current_ma = 4;
  }
  setBank(true); // //Access registers 0x20 to 0x7F

  Adafruit_BusIO_Register led_reg =
      Adafruit_BusIO_Register(AS7343_LED);

  // true = led on , false = off
  Adafruit_BusIO_RegisterBits led_current_bits =
      Adafruit_BusIO_RegisterBits(&led_reg, 7, 0);

  bool result = led_current_bits.write((uint8_t)((led_current_ma - 4) / 2));
  setBank(false); // Access registers 0x80 and above (default)
  return result;
}

/**
 * @brief Get the current limit for the LED
 *
 * Range is 4mA to 258mA
 * @return current limit in mA
 */
uint16_t AMS_OSRAM_AS7343::getLEDCurrent(void) {
  uint16_t led_current_ma;
  uint32_t led_raw;

  setBank(true); // Access registers 0x20 to 0x7F

  Adafruit_BusIO_Register led_reg =
      Adafruit_BusIO_Register(AS7343_LED);

  Adafruit_BusIO_RegisterBits led_current_bits =
      Adafruit_BusIO_RegisterBits(&led_reg, 7, 0);

  led_raw = led_current_bits.read();

  led_current_ma = (uint16_t)(led_raw * 2) + 4;
  setBank(false); // Access registers 0x80 and above (default)
  return led_current_ma;
}

/**
 * @brief Sets the active register bank
 *
 * The AS7343 uses banks to organize the register making it nescessary to set
 * the correct bank to access a register.
 *

 * @param low **true**:
 * **false**: Set the current bank to allow access to registers with addresses
 of `0x80` and above
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setBank(bool low) {
  Adafruit_BusIO_Register cfg0_reg =
      Adafruit_BusIO_Register(AS7343_CFG0);
  // register map says shift 3, 0xA9 description says shift 4 with 3 being
  // reserved
  Adafruit_BusIO_RegisterBits bank_bit =
      Adafruit_BusIO_RegisterBits(&cfg0_reg, 1, 4);

  return bank_bit.write(low);
}

/**
 * @brief Sets the threshold below which spectral measurements will trigger
 * interrupts when the APERS count is reached
 *
 * @param low_threshold the new threshold
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setLowThreshold(uint16_t low_threshold) {
  Adafruit_BusIO_Register sp_low_threshold_reg =
      Adafruit_BusIO_Register(AS7343_SP_LOW_TH_L, 2, LSBFIRST);
  return sp_low_threshold_reg.write(low_threshold);
}

/**
 * @brief Returns the current low thighreshold for spectral measurements
 *
 * @return int16_t The current low threshold
 */
uint16_t AMS_OSRAM_AS7343::getLowThreshold(void) {
  Adafruit_BusIO_Register sp_low_threshold_reg =
      Adafruit_BusIO_Register(AS7343_SP_LOW_TH_L, 2, LSBFIRST);
  return (uint16_t)sp_low_threshold_reg.read();
}

/**
 * @brief Sets the threshold above which spectral measurements will trigger
 * interrupts when the APERS count is reached
 *
 * @param high_threshold
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setHighThreshold(uint16_t high_threshold) {
  Adafruit_BusIO_Register sp_high_threshold_reg =
      Adafruit_BusIO_Register(AS7343_SP_HIGH_TH_L, 2, LSBFIRST);
  return sp_high_threshold_reg.write(high_threshold);
}

/**
 * @brief Returns the current high thighreshold for spectral measurements
 *
 * @return int16_t The current high threshold
 */
uint16_t AMS_OSRAM_AS7343::getHighThreshold(void) {
  Adafruit_BusIO_Register sp_high_threshold_reg =
      Adafruit_BusIO_Register(AS7343_SP_HIGH_TH_L, 2, LSBFIRST);
  return (uint16_t)sp_high_threshold_reg.read();
}

/**
 * @brief Enable Interrupts based on spectral measurements
 *
 * @param enable_int true: enable false: disable
 * @return true: success false: falure
 */
bool AMS_OSRAM_AS7343::enableSpectralInterrupt(bool enable_int) {
  Adafruit_BusIO_Register int_enable_reg =
      Adafruit_BusIO_Register(AS7343_INTENAB);
  Adafruit_BusIO_RegisterBits sp_int_bit =
      Adafruit_BusIO_RegisterBits(&int_enable_reg, 1, 3);
  return sp_int_bit.write(enable_int);
}

/**
 * @brief Enabled system interrupts
 *
 * @param enable_int Set to true to enable system interrupts
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::enableSystemInterrupt(bool enable_int) {
  Adafruit_BusIO_Register int_enable_reg =
      Adafruit_BusIO_Register(AS7343_INTENAB);
  Adafruit_BusIO_RegisterBits sien_int_bit =
      Adafruit_BusIO_RegisterBits(&int_enable_reg, 1, 0);
  return sien_int_bit.write(enable_int);
}

// Spectral Interrupt Persistence.
// Defines a filter for the number of consecutive
// occurrences that spectral data must remain outside
// the threshold range between SP_TH_L and
// SP_TH_H before an interrupt is generated. The
// spectral data channel used for the persistence filter
// is set by SP_TH_CHANNEL. Any sample that is
// inside the threshold range resets the counter to 0.

/**
 * @brief Sets the number of times an interrupt threshold must be exceeded
 * before an interrupt is triggered
 *
 * @param cycle_count The number of cycles to trigger an interrupt
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setAPERS(AS7343_int_cycle_count_t cycle_count) {
  Adafruit_BusIO_Register pers_reg =
      Adafruit_BusIO_Register(AS7343_PERS);
  Adafruit_BusIO_RegisterBits apers_bits =
      Adafruit_BusIO_RegisterBits(&pers_reg, 4, 0);
  return apers_bits.write(cycle_count);
}

/**
 * @brief Set the ADC channel to use for spectral thresholds including
 * interrupts, automatic gain control, and persistance settings
 *
 * @param channel The channel to use for spectral thresholds. Must be a
 * AS7343_adc_channel_t **except for** `AS7343_ADC_CHANNEL_5`
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setSpectralThresholdChannel(
    AS7343_adc_channel_t channel) {
  if (channel == AS7343_ADC_CHANNEL_5) {
    return false;
  }
  Adafruit_BusIO_Register cfg_12_reg =
      Adafruit_BusIO_Register(AS7343_CFG12);
  Adafruit_BusIO_RegisterBits spectral_threshold_ch_bits =
      Adafruit_BusIO_RegisterBits(&cfg_12_reg, 3, 0);
  return spectral_threshold_ch_bits.write(channel);
}

/**
 * @brief Returns the current value of the Interupt status register
 *
 * @return uint8_t
 */
uint8_t AMS_OSRAM_AS7343::getInterruptStatus(void) {
  Adafruit_BusIO_Register int_status_reg =
      Adafruit_BusIO_Register(AS7343_STATUS);
  return (uint8_t)int_status_reg.read();
}

/**
 * @brief Returns the status of the spectral measurement threshold interrupts
 *
 * @return true: interrupt triggered false: interrupt not triggered
 */
bool AMS_OSRAM_AS7343::spectralInterruptTriggered(void) {
  Adafruit_BusIO_Register int_status_reg =
      Adafruit_BusIO_Register(AS7343_STATUS);
  Adafruit_BusIO_RegisterBits aint_bit =
      Adafruit_BusIO_RegisterBits(&int_status_reg, 1, 3);

  return aint_bit.read();
}

/**
 * @brief Clear the interrupt status register
 *
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::clearInterruptStatus(void) {
  Adafruit_BusIO_Register int_status_reg =
      Adafruit_BusIO_Register(AS7343_STATUS);

  return int_status_reg.write(0xFF);
}

/**
 * @brief The current state of the spectral measurement interrupt status
 * register
 *
 * @return uint8_t The current status register
 */
uint8_t AMS_OSRAM_AS7343::spectralInterruptSource(void) {
  Adafruit_BusIO_Register status3_reg =
      Adafruit_BusIO_Register(AS7343_STATUS3);

  uint8_t spectral_int_source = (uint8_t)status3_reg.read();
  last_spectral_int_source = spectral_int_source;
  return spectral_int_source;
}

/**
 * @brief The status of the low threshold interrupt
 *
 * @return true: low interrupt triggered false: interrupt not triggered
 */
bool AMS_OSRAM_AS7343::spectralLowTriggered(void) {
  return (last_spectral_int_source & AS7343_SPECTRAL_INT_LOW_MSK) > 0;
}

/**
 * @brief The status of the high threshold interrupt
 *
 * @return true: high interrupt triggered false: interrupt not triggered
 */
bool AMS_OSRAM_AS7343::spectralHighTriggered(void) {
  return (last_spectral_int_source & AS7343_SPECTRAL_INT_HIGH_MSK) > 0;
}

/**
 * @brief
 *
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::getIsDataReady() {
  Adafruit_BusIO_Register status2_reg =
      Adafruit_BusIO_Register(AS7343_STATUS2);
  Adafruit_BusIO_RegisterBits avalid_bit =
      Adafruit_BusIO_RegisterBits(&status2_reg, 1, 6);

	//return 0;
  return avalid_bit.read();
}

/**
 * @brief Configure SMUX for sensors F1-4, Clear and NIR
 *
 */
void AMS_OSRAM_AS7343::setup_F1F4_Clear_NIR() {
  // SMUX Config for F1,F2,F3,F4,NIR,Clear
  writeRegister(uint8_t(0x00), uint8_t(0x30)); // F3 left set to ADC2
  writeRegister(uint8_t(0x01), uint8_t(0x01)); // F1 left set to ADC0
  writeRegister(uint8_t(0x02), uint8_t(0x00)); // Reserved or disabled
  writeRegister(uint8_t(0x03), uint8_t(0x00)); // F8 left disabled
  writeRegister(uint8_t(0x04), uint8_t(0x00)); // F6 left disabled
  writeRegister(
      uint8_t(0x05),
      uint8_t(0x42)); // F4 left connected to ADC3/f2 left connected to ADC1
  writeRegister(uint8_t(0x06), uint8_t(0x00)); // F5 left disbled
  writeRegister(uint8_t(0x07), uint8_t(0x00)); // F7 left disbled
  writeRegister(uint8_t(0x08), uint8_t(0x50)); // CLEAR connected to ADC4
  writeRegister(uint8_t(0x09), uint8_t(0x00)); // F5 right disabled
  writeRegister(uint8_t(0x0A), uint8_t(0x00)); // F7 right disabled
  writeRegister(uint8_t(0x0B), uint8_t(0x00)); // Reserved or disabled
  writeRegister(uint8_t(0x0C), uint8_t(0x20)); // F2 right connected to ADC1
  writeRegister(uint8_t(0x0D), uint8_t(0x04)); // F4 right connected to ADC3
  writeRegister(uint8_t(0x0E), uint8_t(0x00)); // F6/F8 right disabled
  writeRegister(uint8_t(0x0F), uint8_t(0x30)); // F3 right connected to AD2
  writeRegister(uint8_t(0x10), uint8_t(0x01)); // F1 right connected to AD0
  writeRegister(uint8_t(0x11), uint8_t(0x50)); // CLEAR right connected to AD4
  writeRegister(uint8_t(0x12), uint8_t(0x00)); // Reserved or disabled
  writeRegister(uint8_t(0x13), uint8_t(0x06)); // NIR connected to ADC5
}

/**
 * @brief Configure SMUX for sensors F5-8, Clear and NIR
 *
 */
void AMS_OSRAM_AS7343::setup_F5F8_Clear_NIR() {
  // SMUX Config for F5,F6,F7,F8,NIR,Clear
  writeRegister(uint8_t(0x00), uint8_t(0x00)); // F3 left disable
  writeRegister(uint8_t(0x01), uint8_t(0x00)); // F1 left disable
  writeRegister(uint8_t(0x02), uint8_t(0x00)); // reserved/disable
  writeRegister(uint8_t(0x03), uint8_t(0x40)); // F8 left connected to ADC3
  writeRegister(uint8_t(0x04), uint8_t(0x02)); // F6 left connected to ADC1
  writeRegister(uint8_t(0x05), uint8_t(0x00)); // F4/ F2 disabled
  writeRegister(uint8_t(0x06), uint8_t(0x10)); // F5 left connected to ADC0
  writeRegister(uint8_t(0x07), uint8_t(0x03)); // F7 left connected to ADC2
  writeRegister(uint8_t(0x08), uint8_t(0x50)); // CLEAR Connected to ADC4
  writeRegister(uint8_t(0x09), uint8_t(0x10)); // F5 right connected to ADC0
  writeRegister(uint8_t(0x0A), uint8_t(0x03)); // F7 right connected to ADC2
  writeRegister(uint8_t(0x0B), uint8_t(0x00)); // Reserved or disabled
  writeRegister(uint8_t(0x0C), uint8_t(0x00)); // F2 right disabled
  writeRegister(uint8_t(0x0D), uint8_t(0x00)); // F4 right disabled
  writeRegister(
      uint8_t(0x0E),
      uint8_t(0x24)); // F8 right connected to ADC2/ F6 right connected to ADC1
  writeRegister(uint8_t(0x0F), uint8_t(0x00)); // F3 right disabled
  writeRegister(uint8_t(0x10), uint8_t(0x00)); // F1 right disabled
  writeRegister(uint8_t(0x11), uint8_t(0x50)); // CLEAR right connected to AD4
  writeRegister(uint8_t(0x12), uint8_t(0x00)); // Reserved or disabled
  writeRegister(uint8_t(0x13), uint8_t(0x06)); // NIR connected to ADC5
}

/**
 * @brief Configure SMUX for flicker detection
 *
 */
void AMS_OSRAM_AS7343::FDConfig() {
  // SMUX Config for Flicker- register (0x13)left set to ADC6 for flicker
  // detection
  writeRegister(uint8_t(0x00), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x01), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x02), uint8_t(0x00)); // reserved/disabled
  writeRegister(uint8_t(0x03), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x04), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x05), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x06), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x07), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x08), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x09), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x0A), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x0B), uint8_t(0x00)); // Reserved or disabled
  writeRegister(uint8_t(0x0C), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x0D), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x0E), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x0F), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x10), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x11), uint8_t(0x00)); // disabled
  writeRegister(uint8_t(0x12), uint8_t(0x00)); // Reserved or disabled
  writeRegister(uint8_t(0x13),
                uint8_t(0x60)); // Flicker connected to ADC5 to left of 0x13
}

// TODO; check for valid values
/**
 * @brief Sets the integration time step count
 *
 * Total integration time will be `(ATIME + 1) * (ASTEP + 1) * 2.78µS`
 *
 * @param atime_value The integration time step count
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setATIME(uint8_t atime_value) {
  Adafruit_BusIO_Register atime_reg =
      Adafruit_BusIO_Register(AS7343_ATIME);
  return atime_reg.write(atime_value);
}

/**
 * @brief Returns the integration time step count
 *
 * Total integration time will be `(ATIME + 1) * (ASTEP + 1) * 2.78µS`
 *
 * @return uint8_t The current integration time step count
 */
uint8_t AMS_OSRAM_AS7343::getATIME() {
  Adafruit_BusIO_Register atime_reg =
      Adafruit_BusIO_Register(AS7343_ATIME);
  return (uint8_t)atime_reg.read();
}

/**
 * @brief Sets the integration time step size
 *
 * @param astep_value Integration time step size in 2.78 microsecon increments
 * Step size is `(astep_value+1) * 2.78 uS`
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setASTEP(uint16_t astep_value) {
  Adafruit_BusIO_Register astep_reg =
      Adafruit_BusIO_Register(AS7343_ASTEP_L, 2, LSBFIRST);
  return astep_reg.write(astep_value);
}

/**
 * @brief Returns the integration time step size
 *
 * Step size is `(astep_value+1) * 2.78 uS`
 *
 * @return uint16_t The current integration time step size
 */
uint16_t AMS_OSRAM_AS7343::getASTEP() {
  Adafruit_BusIO_Register astep_reg =
      Adafruit_BusIO_Register(AS7343_ASTEP_L, 2, LSBFIRST);
  return (uint16_t)astep_reg.read();
}

/**
 * @brief Sets the ADC gain multiplier
 *
 * @param gain_value The gain amount. must be an `AS7343_gain_t`
 * @return true: success false: failure
 */
bool AMS_OSRAM_AS7343::setGain(AS7343_gain_t gain_value) {
  Adafruit_BusIO_Register cfg1_reg =
      Adafruit_BusIO_Register(AS7343_CFG1);
  return cfg1_reg.write(gain_value);
  // AGAIN bitfield is only[0:4] but the rest is empty
}

/**
 * @brief Returns the ADC gain multiplier
 *
 * @return AS7343_gain_t The current ADC gain multiplier
 */
AS7343_gain_t AMS_OSRAM_AS7343::getGain() {
  Adafruit_BusIO_Register cfg1_reg =
      Adafruit_BusIO_Register(AS7343_CFG1);
  return (AS7343_gain_t)cfg1_reg.read();
}

/**
 * @brief Returns the integration time
 *
 * The integration time is `(ATIME + 1) * (ASTEP + 1) * 2.78µS`
 *
 * @return long The current integration time in ms
 */
long AMS_OSRAM_AS7343::getTINT() {
  uint16_t astep = getASTEP();
  uint8_t atime = getATIME();

  return (long)((atime + 1) * (astep + 1) * 2.78 / 1000);
}

/**
 * @brief Converts raw ADC values to basic counts
 *
 * The basic counts are `RAW/(GAIN * TINT)`
 *
 * @param raw The raw ADC values to convert
 *
 * @return float The basic counts
 */
double AMS_OSRAM_AS7343::toBasicCounts(uint16_t raw) {
  float gain_val = 0;
  AS7343_gain_t gain = getGain();
  switch (gain) {
  case AS7343_GAIN_0_5X:
    gain_val = 0.5;
    break;
  case AS7343_GAIN_1X:
    gain_val = 1;
    break;
  case AS7343_GAIN_2X:
    gain_val = 2;
    break;
  case AS7343_GAIN_4X:
    gain_val = 4;
    break;
  case AS7343_GAIN_8X:
    gain_val = 8;
    break;
  case AS7343_GAIN_16X:
    gain_val = 16;
    break;
  case AS7343_GAIN_32X:
    gain_val = 32;
    break;
  case AS7343_GAIN_64X:
    gain_val = 64;
    break;
  case AS7343_GAIN_128X:
    gain_val = 128;
    break;
  case AS7343_GAIN_256X:
    gain_val = 256;
    break;
  case AS7343_GAIN_512X:
    gain_val = 512;
    break;
  case AS7343_GAIN_1024X:
      gain_val = 1024;
      break;
  case AS7343_GAIN_2048X:
        gain_val = 2048;
        break;
  }
  return raw / (gain_val * (getATIME() + 1) * (getASTEP() + 1) * 2.78 / 1000);
}

/**
 * @brief Detect a flickering light
 * @return The frequency of a detected flicker or 1 if a flicker of
 * unknown frequency is detected
 */
uint16_t AMS_OSRAM_AS7343::detectFlickerHz(void) {
  // bool isEnabled = true;
  // bool isFdmeasReady = false;

  // disable everything; Flicker detect, smux, wait, spectral, power
  disableAll();
  // re-enable power
  powerEnable(true);

  // Write SMUX configuration from RAM to set SMUX chain registers (Write 0x10
  // to CFG6)
  setSMUXCommand(AS7343_SMUX_CMD_WRITE);

  // Write new configuration to all the 20 registers for detecting Flicker
  FDConfig();

  // Start SMUX command
  enableSMUX();

  // Enable SP_EN bit
  enableSpectralMeasurement(true);

  // Enable flicker detection bit
  writeRegister(uint8_t(AS7343_ENABLE), uint8_t(0x41));
  R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS); // SF 2020-08-12 Does this really need to be so long?
  uint16_t flicker_status = getFlickerDetectStatus();
  enableFlickerDetection(false);
  switch (flicker_status) {
  case 44:
    return 1;
  case 45:
    return 100;
  case 46:
    return 120;
  default:
    return 0;
  }
}

/**
 * @brief Write a uint8_t to the given register
 *
 * @param addr Register address
 * @param val The value to set the register to
 */
void AMS_OSRAM_AS7343::writeRegister(uint8_t addr, uint8_t val) {
  Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(addr);
  reg.write(val);
}

bool AMS_OSRAM_AS7343::digitalSaturation(void) {
  Adafruit_BusIO_Register status2_reg =
      Adafruit_BusIO_Register(AS7343_STATUS2);
  Adafruit_BusIO_RegisterBits asat_digital_bit =
      Adafruit_BusIO_RegisterBits(&status2_reg, 1, 4);

  return asat_digital_bit.read();
}

bool AMS_OSRAM_AS7343::analogSaturation(void) {
  Adafruit_BusIO_Register status2_reg =
      Adafruit_BusIO_Register(AS7343_STATUS2);
  Adafruit_BusIO_RegisterBits asat_analog_bit =
      Adafruit_BusIO_RegisterBits(&status2_reg, 1, 3);

  return asat_analog_bit.read();
}


bool AMS_OSRAM_AS7343::clearDigitalSaturationStatus(void) {
  Adafruit_BusIO_Register status2_reg =
      Adafruit_BusIO_Register(AS7343_STATUS2);
  Adafruit_BusIO_RegisterBits asat_digital_bit =
      Adafruit_BusIO_RegisterBits(&status2_reg, 1, 4);
  return asat_digital_bit.write(0);
}

bool AMS_OSRAM_AS7343::clearAnalogSaturationStatus(void) {
  Adafruit_BusIO_Register status2_reg =
      Adafruit_BusIO_Register(AS7343_STATUS2);
  Adafruit_BusIO_RegisterBits asat_analog_bit =
      Adafruit_BusIO_RegisterBits(&status2_reg, 1, 3);
  return asat_analog_bit.write(0);
}

#endif
