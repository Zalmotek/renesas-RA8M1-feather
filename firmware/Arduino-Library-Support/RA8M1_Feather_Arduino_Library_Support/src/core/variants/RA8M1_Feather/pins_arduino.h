#pragma once

#include "hal_data.h"

#define PIN(X,Y) (X * 16 + Y)

// Pin count
// ----
#ifdef __cplusplus
extern "C" unsigned int PINCOUNT_fn();
#endif
#define PINS_COUNT           (PINCOUNT_fn())
#define NUM_DIGITAL_PINS     (15u)
#define NUM_ANALOG_INPUTS    (6u)
#define NUM_ANALOG_OUTPUTS   (0u)

#define PIN_A0   (15u)
#define PIN_A1   (16u)
#define PIN_A2   (17u)
#define PIN_A3   (18u)
#define PIN_A4   (19u)
#define PIN_A5   (20u)

#define DAC8_HOWMANY (0)
#define DAC12_HOWMANY (1)
#define DAC         A0
#define IS_DAC(x)   (x == DAC ? true : false)
#define DAC_ADDRESS_12_CH0          R_DAC_BASE

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;

// Digital pins
// -----------
#define PIN_D5   (5u)
#define PIN_D6   (6u)
#define PIN_D9   (9u)
#define PIN_D10   (10u)
#define PIN_D11   (11u)
#define PIN_D12   (12u)
#define PIN_D13   (13u)
#define PIN_D14   (14u)

#undef D5
#undef D6
#undef D9
#undef D10
#undef D11
#undef D12
#undef D13
#undef D14
static const uint8_t D5 = PIN_D5;
static const uint8_t D6 = PIN_D6;
static const uint8_t D9 = PIN_D9;
static const uint8_t D10 = PIN_D10;
static const uint8_t D11 = PIN_D11;
static const uint8_t D12 = PIN_D12;
static const uint8_t D13 = PIN_D13;
static const uint8_t D14 = PIN_D14;

#define digitalPinHasPWM(p) (IS_PIN_PWM(getPinCfgs(p, PIN_CFG_REQ_PWM)[0]))
// LEDs
// ----
#define PIN_LED     (13u)
#define LED_BUILTIN PIN_LED

/****** RTC CORE DEFINES *******/
//#define RTC_HOWMANY     1
#define RTC_HOWMANY     0


/****** UART CORE DEFINES ******/

#define SERIAL_HOWMANY		3
#define UART1_TX_PIN        7
#define UART1_RX_PIN        8

#define UART2_TX_PIN        9
#define UART2_RX_PIN        6

#define UART3_TX_PIN        10
#define UART3_RX_PIN        11

/****** WIRE CORE DEFINES ******/

#define WIRE_HOWMANY      1
#define WIRE_SDA_PIN      4
#define WIRE_SCL_PIN      3

static const uint8_t SDA = WIRE_SDA_PIN;
static const uint8_t SCL = WIRE_SCL_PIN;

/****** SPI CORE DEFINES ******/

#define SPI_HOWMANY       1

#define PIN_SPI_MOSI  (1)
#define PIN_SPI_MISO  (0)
#define PIN_SPI_SCK   (2)
//#define PIN_SPI_CS    (10)
#define FORCE_SPI_MODE  (MODE_SPI)

#undef MISO
#undef MOSI
#undef SCK

static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;
//static const uint8_t CS  =  PIN_SPI_CS;
//static const uint8_t SS  =  PIN_SPI_CS;

/****** GTP CORE DEFINES *******/

#define GTP32_HOWMANY     8
#define GTP16_HOWMANY     6
#define GPT_HOWMANY       14

/****** AGT CORE DEFINES *******/
//#define AGT_HOWMANY       2
#define AGT_HOWMANY       1

/****** CAN CORE DEFINES ******/

//#define CAN_HOWMANY       1
#define CAN_HOWMANY       0

//#define PIN_CAN0_TX       (4)
//#define PIN_CAN0_RX       (5)
//#define PIN_CAN0_STBY    (-1)

#define EXT_INTERRUPTS_HOWMANY 3

//#define AVCC_MEASURE_PIN        20
//#define AVCC_MULTIPLY_FACTOR    8.33

//#define AR_INTERNAL_VOLTAGE     1.43f

#define USB_VID           (0x0045)
#define USB_PID           (0x5310)
#define USB_NAME          "RA8M1 Feather"

#define VUSB_LDO_ENABLE     1

/* EEPROM DEFINES */

//#define ARDUINO_FLASH_TYPE  LP_FLASH
//#define FLASH_BASE_ADDRESS  0x40100000
//#define FLASH_TOTAL_SIZE    0x2000
//#define FLASH_BLOCK_SIZE    0x400

