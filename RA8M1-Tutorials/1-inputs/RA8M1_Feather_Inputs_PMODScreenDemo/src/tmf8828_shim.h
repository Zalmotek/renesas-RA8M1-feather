/*
 *****************************************************************************
 * Copyright by ams OSRAM AG                                                       *
 * All rights are reserved.                                                  *
 *                                                                           *
 * IMPORTANT - PLEASE READ CAREFULLY BEFORE COPYING, INSTALLING OR USING     *
 * THE SOFTWARE.                                                             *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS         *
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT          *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
 *****************************************************************************
 */

#ifndef TMF8828_SHIM_H
#define TMF8828_SHIM_H

// This is the shim for the arduino uno.
// Any define, macro and/or function herein must be adapted to match your
// target platform

// ---------------------------------------------- includes ----------------------------------------

#include "Wire.h"

// ---------------------------------------------- defines -----------------------------------------

#define ARDUINO_MAX_I2C_TRANSFER    32

// on the arduino uno the enable pin is connected to digital 6, interrupt to digital 7
#define ENABLE_PIN                            6
#define INTERRUPT_PIN                         7

// for 2nd tmf8828 on the arduino uno the alternate enable pin is connected to digital 4, alternate interrupt to digital 5
#define ALT_ENABLE_PIN                            4
#define ALT_INTERRUPT_PIN                         5

#define TMF8828_NUMBER_RESULT_RECORDS   4                 // TMF8828 has 4 result records to report all 64 results

// print only the first xx results, it this is more than total exist, it will be shortend to (36== maximum)
#define PRINT_NUMBER_RESULTS        36

// Histogram dumping requires sub-packets
// Register offset of sub-packets
#define TMF8828_COM_SUBPACKET_NUMBER                          0x24      // sub-packet number
#define TMF8828_COM_SUBPACKET_PAYLOAD                         0x25      // sub-packet payload
#define TMF8828_COM_SUBPACKET_CFG_IDX                         0x26      // sub-packet config index (0,1)
#define TMF8828_COM_SUBPACKET_PAYLOAD_0                       0x27
#define TMF8828_COM_HISTOGRAM_PACKET_SIZE                     (4+3+128) // 4 bytes packet header, 3 bytes sub-packet header, 128 paylaod
#define TMF8828_COM_OPTIONAL_SUBPACKET_HEADER_MASK            (0x80)                          /*!< this is the bit that has to be set to indicated in the RID that there is a sub-packet header */
#define TMF8828_COM_HIST_DUMP__histogram__raw_24_bit_histogram 1 // Raw 24 bit histogram
#define TMF8828_COM_HIST_DUMP__histogram__electrical_calibration_24_bit_histogram 2 // Electrical calibration 24 bit histogram
#define TMF8828_NUMBER_OF_BINS_PER_CHANNEL                    128       // how many bins are in a raw histogram per channel

// Clock correction pairs must be a power of 2 value.
#define CLK_CORRECTION_PAIRS                4   // how many clock correction pairs are stored

// some more info registers from the results page
#define TMF8828_COM_RESULT_NUMBER         0x24
#define TMF8828_COM_TEMPERATURE           0x25
#define TMF8828_COM_NUMBER_VALID_RESULTS  0x26
#define TMF8828_COM_SYS_TICK_0            0x34      // sys tick is 4 bytes

// each of the result records consist of 3 bytes
#define TMF8828_COM_RES_CONFIDENCE_0      0x38
#define TMF8828_COM_RES_DISTANCE_0_LSB    0x39
#define TMF8828_COM_RES_DISTANCE_0_MSB    0x3a

// result page addresses and defines
#define TMF8828_COM_CONFIG_RESULT                           0x20  // config/result register address
#define TMF8828_COM_CONFIG_RESULT__measurement_result       0x10  // page contains measurment result
#define TMF8828_COM_CONFIG_RESULT__measurement_result_size  (0xa4-0x20)

// Use this macro like this: data[ RESULT_REG( RESULT_NUMBER ) ], it calculates the offset into the data buffer
#define RESULT_REG( regName )             ( (TMF8828_COM_##regName) - (TMF8828_COM_CONFIG_RESULT) )

// ---------------------------------------------- logging -----------------------------------------

#define LOG_LEVEL_NONE              0
#define LOG_LEVEL_ERROR             1           // only error logging - recommended
#define LOG_LEVEL_CLK_CORRECTION    8           // this is a bit-mask check for clock correction logging
#define LOG_LEVEL_INFO              0x10        // some information
#define LOG_LEVEL_VERBOSE           0x20        // very chatty firmware
#define LOG_LEVEL_I2C               0x80        // this is a bit-mask check for i2c logging
#define LOG_LEVEL_DEBUG             0xFF        // everything

#define TMF8828_COM_APP_ID                                  0x0   // register address
#define TMF8828_COM_APP_ID__application                     0x3   // measurement application id
#define TMF8828_COM_APP_ID__bootloader                      0x80  // bootloader application id

#define TMF8828_COM_TMF8828_MODE                            0x10 // mode register is either 0x00 == tmf8820/1 or 0x08 == tmf8828
#define TMF8828_COM_TMF8828_MODE__mode__TMF8821             0    // the device is operating in 3x3/3x6/4x4 (TMF8820/TMF8821) mode
#define TMF8828_COM_TMF8828_MODE__mode__TMF8828             8

// ---------------------------------------------- macros ------------------------------------------

// on the arduino the HEX file is placed inside the program memory region, so we need a special
// read function to access it
//#define READ_PROGRAM_MEMORY_BYTE( address )   pgm_read_byte( address )

// control the arduino digital pins for enable and interrupt
//#define PIN_OUTPUT( pin )                     pinMode( (pin), OUTPUT )
//#define PIN_INPUT( pin )                      pinMode( (pin), INPUT )

//#define PIN_HIGH( pin )                       digitalWrite( (pin), HIGH )
//#define PIN_LOW( pin )                        digitalWrite( (pin), LOW )

// to replace the arduino specific printing
#define PRINT_CHAR(c)                         APP_PRINT("%c", c)
#define PRINT_INT(i)                          APP_PRINT("%d", i)
#define PRINT_INT_HEX(i)                      APP_PRINT("%x", i)
#define PRINT_STR(str)                        APP_PRINT( str )
#define PRINT_LN()                            APP_PRINT( "\n" )

// Which character to use to seperate the entries in printing
#define SEPERATOR                             ','

// for clock correction insert here the number in relation to your host
#define HOST_TICKS_PER_US                     1         // host counts ticks every microsecond
#define TMF8828_TICKS_PER_US                  5         // tmf8828 counts ticks 0.2 mircosecond (5x faster than host)               

// ---------------------------------------------- types -------------------------------------------

// Each tmf8828 driver instance needs a data structure like this
typedef struct _tmf8828Driver
{
  uint32_t hostTicks[ CLK_CORRECTION_PAIRS ];       // host ticks for clock correction
  uint32_t tmf8828Ticks[ CLK_CORRECTION_PAIRS ];    // device ticks for clock correction
  uint8_t clkCorrectionIdx;                         // index of the last inserted pair
  uint8_t i2cSlaveAddress;                          // i2c slave address to talk to device
  uint8_t clkCorrectionEnable;                      // default is clock correction on
  uint8_t enablePin;                                // which pin to use for enable line
  uint8_t interruptPin;                             // which pin to use for interrupt line
  uint8_t logLevel;                                 // how chatty the program is
} tmf8828Driver;

// ---------------------------------------------- functions ---------------------------------------

// Function to allow to wait for some time in microseconds
// wait ... number of microseconds to wait before this functionr returns
void delay_in_microseconds( uint32_t wait );

// Function returns the current sys-tick. 
uint32_t get_sys_tick( );

// I2C transmit only function.
// reg ... the register address to write to
// buf ... pointer to a byte-array that will be transmitted
// len ... number of bytes in the buffer to transmit
void i2c_tx( uint8_t slave_addr, uint8_t reg, const uint8_t * buf, uint8_t len );

// I2C receive only function.
// reg ... the register address to read from
// buf ... pointer to a byte-array where the received bytes will be written to
// len ... number of bytes to receive 
void i2c_rx( uint8_t slave_addr, uint8_t reg, uint8_t * buf, uint8_t len );

// Function to print the results in a kind of CSV like format
// driver ... pointer to the tmf8828 driver structure 
// data ... pointer to the result structure as defined for tmf882x
// len ... number of bytes the pointer points to
void print_results( tmf8828Driver * driver, uint8_t * data, uint8_t len, int *conf, int *dist, int &subcapture_nr );


// Function to print a histogram part in a kind of CSV like format 
// driver ... pointer to the tmf8828 driver structure 
// data ... pointer to the histogram buffer as defined for tmf882x
// len ... number of bytes the pointer points to
void print_histogram( tmf8828Driver * driver, uint8_t * data, uint8_t len );

// Correct the distance based on the clock correction pairs
// driver ... pointer to an instance of the tmf8828 driver data structure
uint16_t tmf8828CorrectDistance( tmf8828Driver * driver, uint16_t distance );

// Convert 4 bytes in little endian format into an uint32_t
uint32_t tmf8828GetUint32( uint8_t * data );

uint8_t logLevel = 0;

void delay_in_microseconds ( uint32_t wait )
{
  //delayMicroseconds( wait );
	R_BSP_SoftwareDelay(wait, BSP_DELAY_UNITS_MICROSECONDS);
}

void i2c_tx ( uint8_t slave_addr, uint8_t reg, const uint8_t *buf, uint8_t len )
{  // split long transfers into max of 32-bytes
  do
  {
    uint8_t tx;
    if ( len > ARDUINO_MAX_I2C_TRANSFER - 1)
    {
      tx = ARDUINO_MAX_I2C_TRANSFER - 1;
    }
    else
    {
      tx = len; // less than 31 bytes
    }
    if ( logLevel & LOG_LEVEL_I2C )
    {
      PRINT_STR( "I2C-TX (0x" );
      PRINT_INT_HEX( slave_addr );
      PRINT_STR( ") Reg=0x" );
      PRINT_INT_HEX( reg );
      uint8_t dump_len = tx;
      if ( dump_len )
      {
        PRINT_STR( " len=" );
        PRINT_INT( dump_len );
        if ( logLevel >= LOG_LEVEL_DEBUG )
        {
          const uint8_t * dump = buf;
          while ( dump_len-- )
          {
            PRINT_STR( " 0x" );
            PRINT_INT_HEX( *dump );
            dump++;
          }
        }
      }
      PRINT_LN( );
    }

    //Wire.beginTransmission( slave_addr );
    beginTransmission(slave_addr);
    //Wire.write( reg );
    write(reg);
    //Wire.write( buf, tx );
    for (int i = 0; i < tx; i++) {
    	write(buf[i]);
    }
    len -= tx;
    buf += tx;
    reg += tx;
    //Wire.endTransmission( );
    endTransmission(false);
  } while ( len );
}

void i2c_rx ( uint8_t slave_addr, uint8_t reg, uint8_t *buf, uint8_t len )
{   // split long transfers into max of 32-bytes
	do
	{
		if ( logLevel & LOG_LEVEL_I2C )
		{
		  PRINT_STR( "I2C-RX (0x" );
		  PRINT_INT_HEX( slave_addr );
		  PRINT_STR( ") Reg=0x" );
		  PRINT_INT_HEX( reg );
		}
		//Wire.beginTransmission( slave_addr );
		beginTransmission(slave_addr);
		//Wire.write( reg );
		write(reg);
		//Wire.endTransmission( );
		endTransmission(false);
		uint8_t rx;
		uint8_t * dump = buf; // in case we dump on uart, we need the pointer
		if ( len > ARDUINO_MAX_I2C_TRANSFER )
		{
		  rx = ARDUINO_MAX_I2C_TRANSFER;
		}
		else
		{
		  rx = len; // less than 32 bytes
		}
		//Wire.requestFrom( slave_addr, rx );
		requestFrom(slave_addr, rx);
		rx = 0;
		/*
		while ( Wire.available() )
		{  // read in all available bytes
		  *buf = Wire.read();
		  buf++;
		  len--;
		  reg++;
		  rx++;
		}
		*/
		while (available()) {
			*buf = read();
			buf++;
			len--;
			reg++;
			rx++;
		}
		if ( logLevel & LOG_LEVEL_I2C )
		{
		  if ( rx )
		  {
			PRINT_STR( " len=" );
			PRINT_INT( rx );
			if ( logLevel >= LOG_LEVEL_DEBUG )
			{
			  while ( rx-- )
			  {
				PRINT_STR( " 0x" );
				PRINT_INT_HEX( *dump );
				dump++;
			  }
			}
		  }
		  PRINT_LN( );
		}
	  } while ( len );
}


// function prints a single result, and returns incremented pointer
static uint8_t * print_result ( tmf8828Driver * driver, uint8_t * data, int *conf, int *dist, int &idx )
{
  uint8_t confidence = data[0];               // 1st byte is confidence
  uint16_t distance = data[2];                // 3rd byte is MSB distance
  distance = (distance << 8);       // 2nd byte is LSB distnace
  distance = distance + data[1];
  distance = tmf8828CorrectDistance( driver, distance );
  //PRINT_CHAR( SEPERATOR );
  //PRINT_INT( distance );
  //PRINT_CHAR( SEPERATOR );
  //PRINT_INT( confidence );
  int offset = 0;
  if (idx > 35) {
	  offset = 4;
  }
  else if (idx > 26) {
	  offset = 3;
  }
  else if (idx > 17) {
	  offset = 2;
  }
  else if (idx > 8){
	  offset = 1;
  }
  conf[idx - offset] = confidence;
  dist[idx - offset] = distance;
  idx++;
  return data+3;                              // for convenience only, return the new pointer
}

// Results printing:
// #Obj,<i2c_slave_address>,<result_number>,<temperature>,<number_valid_results>,<systick>,<distance_0_mm>,<confidence_0>,<distance_1_mm>,<distance_1>, ...
void print_results ( tmf8828Driver * driver, uint8_t * data, uint8_t len, int *conf, int *dist, int &subcapture_nr )
{
  if ( len >= TMF8828_COM_CONFIG_RESULT__measurement_result_size )
  {
	int cnt = 0;
    int8_t i;
    //uint32_t sysTick = tmf8828GetUint32( data + RESULT_REG( SYS_TICK_0 ) );
    //PRINT_STR( "#Obj" );
    //PRINT_CHAR( SEPERATOR );
    //PRINT_INT( driver->i2cSlaveAddress );
    //PRINT_CHAR( SEPERATOR );
    //PRINT_INT( data[ RESULT_REG( RESULT_NUMBER) ] );
    subcapture_nr = data[ RESULT_REG( RESULT_NUMBER) ];
    //PRINT_CHAR( SEPERATOR );
    //PRINT_INT( data[ RESULT_REG( TEMPERATURE )] );
    //PRINT_CHAR( SEPERATOR );
    //PRINT_INT( data[ RESULT_REG( NUMBER_VALID_RESULTS )] );
    //PRINT_CHAR( SEPERATOR );
    //PRINT_INT( sysTick );
    data = data + RESULT_REG( RES_CONFIDENCE_0 );
    for ( i = 0; i < PRINT_NUMBER_RESULTS ; i++ )
    {
      data = print_result( driver, data, conf, dist, cnt );
    }
    //PRINT_LN( );
  }
  else // result structure too short
  {
    PRINT_STR( "#Err" );
    PRINT_CHAR( SEPERATOR );
    PRINT_STR( "result too short" );
    PRINT_CHAR( SEPERATOR );
    PRINT_INT( len );
    PRINT_LN( );
  }
}

// Print histograms:
// #Raw,<i2c_slave_address>,<sub_packet_number>,<data_0>,<data_1>,..,,<data_127>
// #Cal,<i2c_slave_address>,<sub_packet_number>,<data_0>,<data_1>,..,,<data_127>
void print_histogram ( tmf8828Driver * driver, uint8_t * data, uint8_t len )
{
  if ( len >= TMF8828_COM_HISTOGRAM_PACKET_SIZE )
  {
    uint8_t i;
    uint8_t * ptr = &( data[ RESULT_REG( SUBPACKET_PAYLOAD_0 ) ] );
    if ( data[0] & TMF8828_COM_HIST_DUMP__histogram__raw_24_bit_histogram )
    {
      PRINT_STR( "#Raw" );
    }
    else if ( data[0] & TMF8828_COM_HIST_DUMP__histogram__electrical_calibration_24_bit_histogram )
    {
      PRINT_STR( "#Cal" );
    }
    else
    {
      PRINT_STR( "#???" );
    }
    PRINT_CHAR( SEPERATOR );
    PRINT_INT( driver->i2cSlaveAddress );
    PRINT_CHAR( SEPERATOR );
    PRINT_INT( data[ RESULT_REG( SUBPACKET_NUMBER ) ] );          // print the sub-packet number indicating the third-of-a-channel/tdc the histogram belongs to

    for ( i = 0; i < TMF8828_NUMBER_OF_BINS_PER_CHANNEL ; i++, ptr++ )
    {
      PRINT_CHAR( SEPERATOR );
      PRINT_INT( *ptr );
    }
    PRINT_LN( );
  }
  // else structure too short
}

#endif
