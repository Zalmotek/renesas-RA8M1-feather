/*!
 * @file Adafruit_NeoPixel.cpp
 *
 * @mainpage Arduino Library for driving Adafruit NeoPixel addressable LEDs,
 * FLORA RGB Smart Pixels and compatible devicess -- WS2811, WS2812, WS2812B,
 * SK6812, etc.
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for Adafruit's NeoPixel library for the
 * Arduino platform, allowing a broad range of microcontroller boards
 * (most AVR boards, many ARM devices, ESP8266 and ESP32, among others)
 * to control Adafruit NeoPixels, FLORA RGB Smart Pixels and compatible
 * devices -- WS2811, WS2812, WS2812B, SK6812, etc.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing products
 * from Adafruit!
 *
 * @section author Author
 *
 * Written by Phil "Paint Your Dragon" Burgess for Adafruit Industries,
 * with contributions by PJRC, Michael Miller and other members of the
 * open source community.
 *
 * @section license License
 *
 * This file is part of the Adafruit_NeoPixel library.
 *
 * Adafruit_NeoPixel is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Adafruit_NeoPixel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with NeoPixel. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ADAFRUIT_NEOPIXEL_H
#define ADAFRUIT_NEOPIXEL_H

#include "common_utils.h"
#include "gpt_timer.h"

void delay(int t);
void delay(int t) {
    R_BSP_SoftwareDelay(t, BSP_DELAY_UNITS_MILLISECONDS);
}

#define OUTPUT false
#define INPUT true
#define LOW false
#define HIGH true

char tolower(char c);
char tolower(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

void digitalWrite(int pin, bool state);
void digitalWrite(int pin, bool state) {
    fsp_err_t err = R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, (bsp_io_level_t)state);
    if(FSP_SUCCESS != err) {
        __BKPT(0);
    }
}

void pinMode(int pin, bool state);
void pinMode(int pin, bool state) {
    fsp_err_t err = FSP_SUCCESS;
    if (state == OUTPUT) {
        err = R_IOPORT_PinCfg(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_LOW);
    }
    else if (state == INPUT) {
        err = R_IOPORT_PinCfg(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, IOPORT_CFG_PORT_DIRECTION_INPUT);
    }
    if(FSP_SUCCESS != err) {
        __BKPT(0);
    }
}

// The order of primary colors in the NeoPixel data stream can vary among
// device types, manufacturers and even different revisions of the same
// item.  The third parameter to the Adafruit_NeoPixel constructor encodes
// the per-pixel byte offsets of the red, green and blue primaries (plus
// white, if present) in the data stream -- the following #defines provide
// an easier-to-use named version for each permutation. e.g. NEO_GRB
// indicates a NeoPixel-compatible device expecting three bytes per pixel,
// with the first byte transmitted containing the green value, second
// containing red and third containing blue. The in-memory representation
// of a chain of NeoPixels is the same as the data-stream order; no
// re-ordering of bytes is required when issuing data to the chain.
// Most of these values won't exist in real-world devices, but it's done
// this way so we're ready for it (also, if using the WS2811 driver IC,
// one might have their pixels set up in any weird permutation).

// Bits 5,4 of this value are the offset (0-3) from the first byte of a
// pixel to the location of the red color byte.  Bits 3,2 are the green
// offset and 1,0 are the blue offset.  If it is an RGBW-type device
// (supporting a white primary in addition to R,G,B), bits 7,6 are the
// offset to the white byte...otherwise, bits 7,6 are set to the same value
// as 5,4 (red) to indicate an RGB (not RGBW) device.
// i.e. binary representation:
// 0bWWRRGGBB for RGBW devices
// 0bRRRRGGBB for RGB

// RGB NeoPixel permutations; white and red offsets are always same
// Offset:        W          R          G          B
#define NEO_RGB ((0 << 6) | (0 << 4) | (1 << 2) | (2)) ///< Transmit as R,G,B
#define NEO_RBG ((0 << 6) | (0 << 4) | (2 << 2) | (1)) ///< Transmit as R,B,G
#define NEO_GRB ((1 << 6) | (1 << 4) | (0 << 2) | (2)) ///< Transmit as G,R,B
#define NEO_GBR ((2 << 6) | (2 << 4) | (0 << 2) | (1)) ///< Transmit as G,B,R
#define NEO_BRG ((1 << 6) | (1 << 4) | (2 << 2) | (0)) ///< Transmit as B,R,G
#define NEO_BGR ((2 << 6) | (2 << 4) | (1 << 2) | (0)) ///< Transmit as B,G,R

// RGBW NeoPixel permutations; all 4 offsets are distinct
// Offset:         W          R          G          B
#define NEO_WRGB ((0 << 6) | (1 << 4) | (2 << 2) | (3)) ///< Transmit as W,R,G,B
#define NEO_WRBG ((0 << 6) | (1 << 4) | (3 << 2) | (2)) ///< Transmit as W,R,B,G
#define NEO_WGRB ((0 << 6) | (2 << 4) | (1 << 2) | (3)) ///< Transmit as W,G,R,B
#define NEO_WGBR ((0 << 6) | (3 << 4) | (1 << 2) | (2)) ///< Transmit as W,G,B,R
#define NEO_WBRG ((0 << 6) | (2 << 4) | (3 << 2) | (1)) ///< Transmit as W,B,R,G
#define NEO_WBGR ((0 << 6) | (3 << 4) | (2 << 2) | (1)) ///< Transmit as W,B,G,R

#define NEO_RWGB ((1 << 6) | (0 << 4) | (2 << 2) | (3)) ///< Transmit as R,W,G,B
#define NEO_RWBG ((1 << 6) | (0 << 4) | (3 << 2) | (2)) ///< Transmit as R,W,B,G
#define NEO_RGWB ((2 << 6) | (0 << 4) | (1 << 2) | (3)) ///< Transmit as R,G,W,B
#define NEO_RGBW ((3 << 6) | (0 << 4) | (1 << 2) | (2)) ///< Transmit as R,G,B,W
#define NEO_RBWG ((2 << 6) | (0 << 4) | (3 << 2) | (1)) ///< Transmit as R,B,W,G
#define NEO_RBGW ((3 << 6) | (0 << 4) | (2 << 2) | (1)) ///< Transmit as R,B,G,W

#define NEO_GWRB ((1 << 6) | (2 << 4) | (0 << 2) | (3)) ///< Transmit as G,W,R,B
#define NEO_GWBR ((1 << 6) | (3 << 4) | (0 << 2) | (2)) ///< Transmit as G,W,B,R
#define NEO_GRWB ((2 << 6) | (1 << 4) | (0 << 2) | (3)) ///< Transmit as G,R,W,B
#define NEO_GRBW ((3 << 6) | (1 << 4) | (0 << 2) | (2)) ///< Transmit as G,R,B,W
#define NEO_GBWR ((2 << 6) | (3 << 4) | (0 << 2) | (1)) ///< Transmit as G,B,W,R
#define NEO_GBRW ((3 << 6) | (2 << 4) | (0 << 2) | (1)) ///< Transmit as G,B,R,W

#define NEO_BWRG ((1 << 6) | (2 << 4) | (3 << 2) | (0)) ///< Transmit as B,W,R,G
#define NEO_BWGR ((1 << 6) | (3 << 4) | (2 << 2) | (0)) ///< Transmit as B,W,G,R
#define NEO_BRWG ((2 << 6) | (1 << 4) | (3 << 2) | (0)) ///< Transmit as B,R,W,G
#define NEO_BRGW ((3 << 6) | (1 << 4) | (2 << 2) | (0)) ///< Transmit as B,R,G,W
#define NEO_BGWR ((2 << 6) | (3 << 4) | (1 << 2) | (0)) ///< Transmit as B,G,W,R
#define NEO_BGRW ((3 << 6) | (2 << 4) | (1 << 2) | (0)) ///< Transmit as B,G,R,W

// Add NEO_KHZ400 to the color order value to indicate a 400 KHz device.
// All but the earliest v1 NeoPixels expect an 800 KHz data stream, this is
// the default if unspecified. Because flash space is very limited on ATtiny
// devices (e.g. Trinket, Gemma), v1 NeoPixels aren't handled by default on
// those chips, though it can be enabled by removing the ifndef/endif below,
// but code will be bigger. Conversely, can disable the NEO_KHZ400 line on
// other MCUs to remove v1 support and save a little space.

#define NEO_KHZ800 0x0000 ///< 800 KHz data transmission
#define NEO_KHZ400 0x0100 ///< 400 KHz data transmission

// If 400 KHz support is enabled, the third parameter to the constructor
// requires a 16-bit value (in order to select 400 vs 800 KHz speed).
// If only 800 KHz is enabled (as is default on ATtiny), an 8-bit value
// is sufficient to encode pixel color order, saving some space.

#ifdef NEO_KHZ400
typedef uint16_t neoPixelType; ///< 3rd arg to Adafruit_NeoPixel constructor
#else
typedef uint8_t neoPixelType; ///< 3rd arg to Adafruit_NeoPixel constructor
#endif

// These two tables are declared outside the Adafruit_NeoPixel class
// because some boards may require oldschool compilers that don't
// handle the C++11 constexpr keyword.

/* A PROGMEM (flash mem) table containing 8-bit unsigned sine wave (0-255).
   Copy & paste this snippet into a Python REPL to regenerate:
import math
for x in range(256):
    print("{:3},".format(int((math.sin(x/128.0*math.pi)+1.0)*127.5+0.5))),
    if x&15 == 15: print
*/
static const uint8_t _NeoPixelSineTable[256] = {
    128, 131, 134, 137, 140, 143, 146, 149, 152, 155, 158, 162, 165, 167, 170,
    173, 176, 179, 182, 185, 188, 190, 193, 196, 198, 201, 203, 206, 208, 211,
    213, 215, 218, 220, 222, 224, 226, 228, 230, 232, 234, 235, 237, 238, 240,
    241, 243, 244, 245, 246, 248, 249, 250, 250, 251, 252, 253, 253, 254, 254,
    254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 251,
    250, 250, 249, 248, 246, 245, 244, 243, 241, 240, 238, 237, 235, 234, 232,
    230, 228, 226, 224, 222, 220, 218, 215, 213, 211, 208, 206, 203, 201, 198,
    196, 193, 190, 188, 185, 182, 179, 176, 173, 170, 167, 165, 162, 158, 155,
    152, 149, 146, 143, 140, 137, 134, 131, 128, 124, 121, 118, 115, 112, 109,
    106, 103, 100, 97,  93,  90,  88,  85,  82,  79,  76,  73,  70,  67,  65,
    62,  59,  57,  54,  52,  49,  47,  44,  42,  40,  37,  35,  33,  31,  29,
    27,  25,  23,  21,  20,  18,  17,  15,  14,  12,  11,  10,  9,   7,   6,
    5,   5,   4,   3,   2,   2,   1,   1,   1,   0,   0,   0,   0,   0,   0,
    0,   1,   1,   1,   2,   2,   3,   4,   5,   5,   6,   7,   9,   10,  11,
    12,  14,  15,  17,  18,  20,  21,  23,  25,  27,  29,  31,  33,  35,  37,
    40,  42,  44,  47,  49,  52,  54,  57,  59,  62,  65,  67,  70,  73,  76,
    79,  82,  85,  88,  90,  93,  97,  100, 103, 106, 109, 112, 115, 118, 121,
    124};

/* Similar to above, but for an 8-bit gamma-correction table.
   Copy & paste this snippet into a Python REPL to regenerate:
import math
gamma=2.6
for x in range(256):
    print("{:3},".format(int(math.pow((x)/255.0,gamma)*255.0+0.5))),
    if x&15 == 15: print
*/
static const uint8_t _NeoPixelGammaTable[256] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,
    1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   3,
    3,   3,   3,   3,   3,   4,   4,   4,   4,   5,   5,   5,   5,   5,   6,
    6,   6,   6,   7,   7,   7,   8,   8,   8,   9,   9,   9,   10,  10,  10,
    11,  11,  11,  12,  12,  13,  13,  13,  14,  14,  15,  15,  16,  16,  17,
    17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  22,  23,  24,  24,  25,
    25,  26,  27,  27,  28,  29,  29,  30,  31,  31,  32,  33,  34,  34,  35,
    36,  37,  38,  38,  39,  40,  41,  42,  42,  43,  44,  45,  46,  47,  48,
    49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  68,  69,  70,  71,  72,  73,  75,  76,  77,  78,  80,  81,
    82,  84,  85,  86,  88,  89,  90,  92,  93,  94,  96,  97,  99,  100, 102,
    103, 105, 106, 108, 109, 111, 112, 114, 115, 117, 119, 120, 122, 124, 125,
    127, 129, 130, 132, 134, 136, 137, 139, 141, 143, 145, 146, 148, 150, 152,
    154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182,
    184, 186, 188, 191, 193, 195, 197, 199, 202, 204, 206, 209, 211, 213, 215,
    218, 220, 223, 225, 227, 230, 232, 235, 237, 240, 242, 245, 247, 250, 252,
    255};

/*!
    @brief  Class that stores state and functions for interacting with
            Adafruit NeoPixels and compatible devices.
*/
class Adafruit_NeoPixel {

public:
  // Constructor: number of LEDs, pin number, LED type
  Adafruit_NeoPixel(uint16_t n, int16_t pin = 6,
                    neoPixelType type = NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel(void);
  ~Adafruit_NeoPixel();

  void begin(void);
  void show(void);
  void setPin(int16_t p);
  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
  void setPixelColor(uint16_t n, uint32_t c);
  void fill(uint32_t c = 0, uint16_t first = 0, uint16_t count = 0);
  void setBrightness(uint8_t);
  void clear(void);
  void updateLength(uint16_t n);
  void updateType(neoPixelType t);
  /*!
    @brief   Check whether a call to show() will start sending data
             immediately or will 'block' for a required interval. NeoPixels
             require a short quiet time (about 300 microseconds) after the
             last bit is received before the data 'latches' and new data can
             start being received. Usually one's sketch is implicitly using
             this time to generate a new frame of animation...but if it
             finishes very quickly, this function could be used to see if
             there's some idle time available for some low-priority
             concurrent task.
    @return  1 or true if show() will start sending immediately, 0 or false
             if show() would block (meaning some idle time is available).
  */
  bool canShow(void) {
    // It's normal and possible for endTime to exceed micros() if the
    // 32-bit clock counter has rolled over (about every 70 minutes).
    // Since both are uint32_t, a negative delta correctly maps back to
    // positive space, and it would seem like the subtraction below would
    // suffice. But a problem arises if code invokes show() very
    // infrequently...the micros() counter may roll over MULTIPLE times in
    // that interval, the delta calculation is no longer correct and the
    // next update may stall for a very long time. The check below resets
    // the latch counter if a rollover has occurred. This can cause an
    // extra delay of up to 300 microseconds in the rare case where a
    // show() call happens precisely around the rollover, but that's
    // neither likely nor especially harmful, vs. other code that might
    // stall for 30+ minutes, or having to document and frequently remind
    // and/or provide tech support explaining an unintuitive need for
    // show() calls at least once an hour.
    uint32_t now = (uint32_t)micros();
    if (endTime > now) {
      endTime = now;
    }
    return (now - endTime) >= 300L;
  }
  /*!
    @brief   Get a pointer directly to the NeoPixel data buffer in RAM.
             Pixel data is stored in a device-native format (a la the NEO_*
             constants) and is not translated here. Applications that access
             this buffer will need to be aware of the specific data format
             and handle colors appropriately.
    @return  Pointer to NeoPixel buffer (uint8_t* array).
    @note    This is for high-performance applications where calling
             setPixelColor() on every single pixel would be too slow (e.g.
             POV or light-painting projects). There is no bounds checking
             on the array, creating tremendous potential for mayhem if one
             writes past the ends of the buffer. Great power, great
             responsibility and all that.
  */
  uint8_t *getPixels(void) const { return pixels; };
  uint8_t getBrightness(void) const;
  /*!
    @brief   Retrieve the pin number used for NeoPixel data output.
    @return  Arduino pin number (-1 if not set).
  */
  int16_t getPin(void) const { return pin; };
  /*!
    @brief   Return the number of pixels in an Adafruit_NeoPixel strip object.
    @return  Pixel count (0 if not set).
  */
  uint16_t numPixels(void) const { return numLEDs; }
  uint32_t getPixelColor(uint16_t n) const;
  /*!
    @brief   An 8-bit integer sine wave function, not directly compatible
             with standard trigonometric units like radians or degrees.
    @param   x  Input angle, 0-255; 256 would loop back to zero, completing
                the circle (equivalent to 360 degrees or 2 pi radians).
                One can therefore use an unsigned 8-bit variable and simply
                add or subtract, allowing it to overflow/underflow and it
                still does the expected contiguous thing.
    @return  Sine result, 0 to 255, or -128 to +127 if type-converted to
             a signed int8_t, but you'll most likely want unsigned as this
             output is often used for pixel brightness in animation effects.
  */
  static uint8_t sine8(uint8_t x) {
    return _NeoPixelSineTable[x]; // 0-255 in, 0-255 out
  }
  /*!
    @brief   An 8-bit gamma-correction function for basic pixel brightness
             adjustment. Makes color transitions appear more perceptially
             correct.
    @param   x  Input brightness, 0 (minimum or off/black) to 255 (maximum).
    @return  Gamma-adjusted brightness, can then be passed to one of the
             setPixelColor() functions. This uses a fixed gamma correction
             exponent of 2.6, which seems reasonably okay for average
             NeoPixels in average tasks. If you need finer control you'll
             need to provide your own gamma-correction function instead.
  */
  static uint8_t gamma8(uint8_t x) {
    return _NeoPixelGammaTable[x]; // 0-255 in, 0-255 out
  }
  /*!
    @brief   Convert separate red, green and blue values into a single
             "packed" 32-bit RGB color.
    @param   r  Red brightness, 0 to 255.
    @param   g  Green brightness, 0 to 255.
    @param   b  Blue brightness, 0 to 255.
    @return  32-bit packed RGB value, which can then be assigned to a
             variable for later use or passed to the setPixelColor()
             function. Packed RGB format is predictable, regardless of
             LED strand color order.
  */
  static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }
  /*!
    @brief   Convert separate red, green, blue and white values into a
             single "packed" 32-bit WRGB color.
    @param   r  Red brightness, 0 to 255.
    @param   g  Green brightness, 0 to 255.
    @param   b  Blue brightness, 0 to 255.
    @param   w  White brightness, 0 to 255.
    @return  32-bit packed WRGB value, which can then be assigned to a
             variable for later use or passed to the setPixelColor()
             function. Packed WRGB format is predictable, regardless of
             LED strand color order.
  */
  static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }
  static uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255);
  /*!
    @brief   A gamma-correction function for 32-bit packed RGB or WRGB
             colors. Makes color transitions appear more perceptially
             correct.
    @param   x  32-bit packed RGB or WRGB color.
    @return  Gamma-adjusted packed color, can then be passed in one of the
             setPixelColor() functions. Like gamma8(), this uses a fixed
             gamma correction exponent of 2.6, which seems reasonably okay
             for average NeoPixels in average tasks. If you need finer
             control you'll need to provide your own gamma-correction
             function instead.
  */
  static uint32_t gamma32(uint32_t x);

  void rainbow(uint16_t first_hue = 0, int8_t reps = 1,
               uint8_t saturation = 255, uint8_t brightness = 255,
               bool gammify = true);

  static neoPixelType str2order(const char *v);

private:
#if defined(ARDUINO_ARCH_RP2040)
  void  rp2040Init(uint8_t pin, bool is800KHz);
  void  rp2040Show(uint8_t pin, uint8_t *pixels, uint32_t numBytes, bool is800KHz);
#endif

protected:
#ifdef NEO_KHZ400 // If 400 KHz NeoPixel support enabled...
  bool is800KHz; ///< true if 800 KHz pixels
#endif
  bool begun;         ///< true if begin() previously called
  uint16_t numLEDs;   ///< Number of RGB LEDs in strip
  uint16_t numBytes;  ///< Size of 'pixels' buffer below
  int16_t pin;        ///< Output pin number (-1 if not yet set)
  uint8_t brightness; ///< Strip brightness 0-255 (stored as +1)
  uint8_t *pixels;    ///< Holds LED color values (3 or 4 bytes each)
  uint8_t rOffset;    ///< Red index within each 3- or 4-byte pixel
  uint8_t gOffset;    ///< Index of green byte
  uint8_t bOffset;    ///< Index of blue byte
  uint8_t wOffset;    ///< Index of white (==rOffset if no white)
  uint32_t endTime;   ///< Latch timing reference
};

/*!
  @brief   NeoPixel constructor when length, pin and pixel type are known
           at compile-time.
  @param   n  Number of NeoPixels in strand.
  @param   p  Arduino pin number which will drive the NeoPixel data in.
  @param   t  Pixel type -- add together NEO_* constants defined in
              Adafruit_NeoPixel.h, for example NEO_GRB+NEO_KHZ800 for
              NeoPixels expecting an 800 KHz (vs 400 KHz) data stream
              with color bytes expressed in green, red, blue order per
              pixel.
  @return  Adafruit_NeoPixel object. Call the begin() function before use.
*/
Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, int16_t p, neoPixelType t)
    : begun(false), brightness(0), pixels(NULL), endTime(0) {
  updateType(t);
  updateLength(n);
  setPin(p);
}

/*!
  @brief   "Empty" NeoPixel constructor when length, pin and/or pixel type
           are not known at compile-time, and must be initialized later with
           updateType(), updateLength() and setPin().
  @return  Adafruit_NeoPixel object. Call the begin() function before use.
  @note    This function is deprecated, here only for old projects that
           may still be calling it. New projects should instead use the
           'new' keyword with the first constructor syntax (length, pin,
           type).
*/
Adafruit_NeoPixel::Adafruit_NeoPixel()
    :
#if defined(NEO_KHZ400)
      is800KHz(true),
#endif
      begun(false), numLEDs(0), numBytes(0), pin(-1), brightness(0),
      pixels(NULL), rOffset(1), gOffset(0), bOffset(2), wOffset(1), endTime(0) {
}

/*!
  @brief   Deallocate Adafruit_NeoPixel object, set data pin back to INPUT.
*/
Adafruit_NeoPixel::~Adafruit_NeoPixel() {
  free(pixels);
  if (pin >= 0)
    pinMode(pin, INPUT);
}

/*!
  @brief   Configure NeoPixel pin for output.
*/
void Adafruit_NeoPixel::begin(void) {
  if (pin >= 0) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  begun = true;
}

/*!
  @brief   Change the length of a previously-declared Adafruit_NeoPixel
           strip object. Old data is deallocated and new data is cleared.
           Pin number and pixel format are unchanged.
  @param   n  New length of strip, in pixels.
  @note    This function is deprecated, here only for old projects that
           may still be calling it. New projects should instead use the
           'new' keyword with the first constructor syntax (length, pin,
           type).
*/
void Adafruit_NeoPixel::updateLength(uint16_t n) {
  free(pixels); // Free existing data (if any)

  // Allocate new data -- note: ALL PIXELS ARE CLEARED
  numBytes = (uint16_t)(n * ((wOffset == rOffset) ? 3 : 4));
  pixels = (uint8_t *)malloc(numBytes);
  memset(pixels, 0, numBytes);
  numLEDs = n;
}

/*!
  @brief   Change the pixel format of a previously-declared
           Adafruit_NeoPixel strip object. If format changes from one of
           the RGB variants to an RGBW variant (or RGBW to RGB), the old
           data will be deallocated and new data is cleared. Otherwise,
           the old data will remain in RAM and is not reordered to the
           new format, so it's advisable to follow up with clear().
  @param   t  Pixel type -- add together NEO_* constants defined in
              Adafruit_NeoPixel.h, for example NEO_GRB+NEO_KHZ800 for
              NeoPixels expecting an 800 KHz (vs 400 KHz) data stream
              with color bytes expressed in green, red, blue order per
              pixel.
  @note    This function is deprecated, here only for old projects that
           may still be calling it. New projects should instead use the
           'new' keyword with the first constructor syntax
           (length, pin, type).
*/
void Adafruit_NeoPixel::updateType(neoPixelType t) {
  bool oldThreeBytesPerPixel = (wOffset == rOffset); // false if RGBW

  wOffset = (t >> 6) & 0b11; // See notes in header file
  rOffset = (t >> 4) & 0b11; // regarding R/G/B/W offsets
  gOffset = (t >> 2) & 0b11;
  bOffset = t & 0b11;
#if defined(NEO_KHZ400)
  is800KHz = (t < 256); // 400 KHz flag is 1<<8
#endif

  // If bytes-per-pixel has changed (and pixel data was previously
  // allocated), re-allocate to new size. Will clear any data.
  if (pixels) {
    bool newThreeBytesPerPixel = (wOffset == rOffset);
    if (newThreeBytesPerPixel != oldThreeBytesPerPixel)
      updateLength(numLEDs);
  }
}

/*!
  @brief   Transmit pixel data in RAM to NeoPixels.
  @note    On most architectures, interrupts are temporarily disabled in
           order to achieve the correct NeoPixel signal timing. This means
           that the Arduino millis() and micros() functions, which require
           interrupts, will lose small intervals of time whenever this
           function is called (about 30 microseconds per RGB pixel, 40 for
           RGBW pixels). There's no easy fix for this, but a few
           specialized alternative or companion libraries exist that use
           very device-specific peripherals to work around it.
*/
void Adafruit_NeoPixel::show(void) {

    if (!pixels)
        return;

  // Data latch = 300+ microsecond pause in the output stream. Rather than
  // put a delay at the end of the function, the ending time is noted and
  // the function will simply hold off (if needed) on issuing the
  // subsequent round of data until the latch time has elapsed. This
  // allows the mainline code to start generating the next frame of data
  // rather than stalling for the latch.
    while (!canShow())
    ;
    // endTime is a private member (rather than global var) so that multiple
    // instances on different pins can be quickly issued in succession (each
    // instance doesn't delay the next).

    // In order to make this code runtime-configurable to work with any pin,
    // SBI/CBI instructions are eschewed in favor of full PORT writes via the
    // OUT or ST instructions. It relies on two facts: that peripheral
    // functions (such as PWM) take precedence on output pins, so our PORT-
    // wide writes won't interfere, and that interrupts are globally disabled
    // while data is being issued to the LEDs, so no other code will be
    // accessing the PORT. The code takes an initial 'snapshot' of the PORT
    // state, computes 'pin high' and 'pin low' values, and writes these back
    // to the PORT register as needed.

    // RENESAS including UNO R4
    // Definition for a single channel clockless controller for RA4M1 (Cortex M4)
    // See clockless.h for detailed info on how the template parameters are used.
    #define ARM_DEMCR               (*(volatile uint32_t *)0xE000EDFC) // Debug Exception and Monitor Control
    #define ARM_DEMCR_TRCENA                (1 << 24)        // Enable debugging & monitoring blocks
    #define ARM_DWT_CTRL            (*(volatile uint32_t *)0xE0001000) // DWT control register
    #define ARM_DWT_CTRL_CYCCNTENA          (1 << 0)                // Enable cycle count
    #define ARM_DWT_CYCCNT          (*(volatile uint32_t *)0xE0001004) // Cycle count register

    #define F_CPU 240000000
    #define CYCLES_800_T0H (F_CPU / 4000000)
    #define CYCLES_800_T1H (F_CPU / 1250000)
    #define CYCLES_800 (F_CPU / 800000)
    #define CYCLES_400_T0H (F_CPU / 2000000)
    #define CYCLES_400_T1H (F_CPU / 833333)
    #define CYCLES_400 (F_CPU / 400000)

      uint8_t *p = pixels, *end = p + numBytes, pix, mask;

      bsp_io_port_pin_t io_pin = (bsp_io_port_pin_t)pin;
      #define PIN_IO_PORT_ADDR(pn)      (R_PORT0 + ((uint32_t) (R_PORT1 - R_PORT0) * ((pn) >> 8u)))

      volatile uint16_t *set = &(PIN_IO_PORT_ADDR(io_pin)->POSR);
      volatile uint16_t *clr = &(PIN_IO_PORT_ADDR(io_pin)->PORR);
      uint16_t msk = (1U << (io_pin & 0xFF));

      uint32_t cyc;

      ARM_DEMCR |= ARM_DEMCR_TRCENA;
      ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;

    #if defined(NEO_KHZ400) // 800 KHz check needed only if 400 KHz support enabled
      if (is800KHz) {
    #endif
        cyc = ARM_DWT_CYCCNT + CYCLES_800;
        while (p < end) {
          pix = *p++;
          for (mask = 0x80; mask; mask >>= 1) {
            while (ARM_DWT_CYCCNT - cyc < CYCLES_800)
              ;
            cyc = ARM_DWT_CYCCNT;
            *set = msk;
            if (pix & mask) {
              while (ARM_DWT_CYCCNT - cyc < CYCLES_800_T1H)
                ;
            } else {
              while (ARM_DWT_CYCCNT - cyc < CYCLES_800_T0H)
                ;
            }
            *clr = msk;
          }
        }
        while (ARM_DWT_CYCCNT - cyc < CYCLES_800)
          ;
    #if defined(NEO_KHZ400)
      } else { // 400 kHz bitstream
        cyc = ARM_DWT_CYCCNT + CYCLES_400;
        while (p < end) {
          pix = *p++;
          for (mask = 0x80; mask; mask >>= 1) {
            while (ARM_DWT_CYCCNT - cyc < CYCLES_400)
              ;
            cyc = ARM_DWT_CYCCNT;
            *set = msk;
            if (pix & mask) {
              while (ARM_DWT_CYCCNT - cyc < CYCLES_400_T1H)
                ;
            } else {
              while (ARM_DWT_CYCCNT - cyc < CYCLES_400_T0H)
                ;
            }
            *clr = msk;
          }
        }
        while (ARM_DWT_CYCCNT - cyc < CYCLES_400)
          ;
      }
    #endif // NEO_KHZ400

      // END ARM ----------------------------------------------------------------

      endTime = (uint32_t)micros(); // Save EOD time for latch on next call
}

/*!
  @brief   Set/change the NeoPixel output pin number. Previous pin,
           if any, is set to INPUT and the new pin is set to OUTPUT.
  @param   p  Arduino pin number (-1 = no pin).
*/
void Adafruit_NeoPixel::setPin(int16_t p) {
  if (begun && (pin >= 0))
    pinMode(pin, INPUT); // Disable existing out pin
  pin = p;
  if (begun) {
    pinMode(p, OUTPUT);
    digitalWrite(p, LOW);
  }
}

/*!
  @brief   Set a pixel's color using separate red, green and blue
           components. If using RGBW pixels, white will be set to 0.
  @param   n  Pixel index, starting from 0.
  @param   r  Red brightness, 0 = minimum (off), 255 = maximum.
  @param   g  Green brightness, 0 = minimum (off), 255 = maximum.
  @param   b  Blue brightness, 0 = minimum (off), 255 = maximum.
*/
void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g,
                                      uint8_t b) {

  if (n < numLEDs) {
    if (brightness) { // See notes in setBrightness()
      r = (uint8_t)((r * brightness) >> 8);
      g = (uint8_t)((g * brightness) >> 8);
      b = (uint8_t)((b * brightness) >> 8);
    }
    uint8_t *p;
    if (wOffset == rOffset) { // Is an RGB-type strip
      p = &pixels[n * 3];     // 3 bytes per pixel
    } else {                  // Is a WRGB-type strip
      p = &pixels[n * 4];     // 4 bytes per pixel
      p[wOffset] = 0;         // But only R,G,B passed -- set W to 0
    }
    p[rOffset] = r; // R,G,B always stored
    p[gOffset] = g;
    p[bOffset] = b;
  }
}

/*!
  @brief   Set a pixel's color using separate red, green, blue and white
           components (for RGBW NeoPixels only).
  @param   n  Pixel index, starting from 0.
  @param   r  Red brightness, 0 = minimum (off), 255 = maximum.
  @param   g  Green brightness, 0 = minimum (off), 255 = maximum.
  @param   b  Blue brightness, 0 = minimum (off), 255 = maximum.
  @param   w  White brightness, 0 = minimum (off), 255 = maximum, ignored
              if using RGB pixels.
*/
void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g,
                                      uint8_t b, uint8_t w) {

  if (n < numLEDs) {
    if (brightness) { // See notes in setBrightness()
      r = (uint8_t)((r * brightness) >> 8);
      g = (uint8_t)((g * brightness) >> 8);
      b = (uint8_t)((b * brightness) >> 8);
      w = (uint8_t)((w * brightness) >> 8);
    }
    uint8_t *p;
    if (wOffset == rOffset) { // Is an RGB-type strip
      p = &pixels[n * 3];     // 3 bytes per pixel (ignore W)
    } else {                  // Is a WRGB-type strip
      p = &pixels[n * 4];     // 4 bytes per pixel
      p[wOffset] = w;         // Store W
    }
    p[rOffset] = r; // Store R,G,B
    p[gOffset] = g;
    p[bOffset] = b;
  }
}

/*!
  @brief   Set a pixel's color using a 32-bit 'packed' RGB or RGBW value.
  @param   n  Pixel index, starting from 0.
  @param   c  32-bit color value. Most significant byte is white (for RGBW
              pixels) or ignored (for RGB pixels), next is red, then green,
              and least significant byte is blue.
*/
void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint32_t c) {
  if (n < numLEDs) {
    uint8_t *p, r = (uint8_t)(c >> 16), g = (uint8_t)(c >> 8), b = (uint8_t)c;
    if (brightness) { // See notes in setBrightness()
      r = (uint8_t)((r * brightness) >> 8);
      g = (uint8_t)((g * brightness) >> 8);
      b = (uint8_t)((b * brightness) >> 8);
    }
    if (wOffset == rOffset) {
      p = &pixels[n * 3];
    } else {
      p = &pixels[n * 4];
      uint8_t w = (uint8_t)(c >> 24);
      p[wOffset] = (brightness ? ((w * brightness) >> 8) : w);
    }
    p[rOffset] = r;
    p[gOffset] = g;
    p[bOffset] = b;
  }
}

/*!
  @brief   Fill all or part of the NeoPixel strip with a color.
  @param   c      32-bit color value. Most significant byte is white (for
                  RGBW pixels) or ignored (for RGB pixels), next is red,
                  then green, and least significant byte is blue. If all
                  arguments are unspecified, this will be 0 (off).
  @param   first  Index of first pixel to fill, starting from 0. Must be
                  in-bounds, no clipping is performed. 0 if unspecified.
  @param   count  Number of pixels to fill, as a positive value. Passing
                  0 or leaving unspecified will fill to end of strip.
*/
void Adafruit_NeoPixel::fill(uint32_t c, uint16_t first, uint16_t count) {
  uint16_t i, end;

  if (first >= numLEDs) {
    return; // If first LED is past end of strip, nothing to do
  }

  // Calculate the index ONE AFTER the last pixel to fill
  if (count == 0) {
    // Fill to end of strip
    end = numLEDs;
  } else {
    // Ensure that the loop won't go past the last pixel
    end = first + count;
    if (end > numLEDs)
      end = numLEDs;
  }

  for (i = first; i < end; i++) {
    this->setPixelColor(i, c);
  }
}

/*!
  @brief   Convert hue, saturation and value into a packed 32-bit RGB color
           that can be passed to setPixelColor() or other RGB-compatible
           functions.
  @param   hue  An unsigned 16-bit value, 0 to 65535, representing one full
                loop of the color wheel, which allows 16-bit hues to "roll
                over" while still doing the expected thing (and allowing
                more precision than the wheel() function that was common to
                prior NeoPixel examples).
  @param   sat  Saturation, 8-bit value, 0 (min or pure grayscale) to 255
                (max or pure hue). Default of 255 if unspecified.
  @param   val  Value (brightness), 8-bit value, 0 (min / black / off) to
                255 (max or full brightness). Default of 255 if unspecified.
  @return  Packed 32-bit RGB with the most significant byte set to 0 -- the
           white element of WRGB pixels is NOT utilized. Result is linearly
           but not perceptually correct, so you may want to pass the result
           through the gamma32() function (or your own gamma-correction
           operation) else colors may appear washed out. This is not done
           automatically by this function because coders may desire a more
           refined gamma-correction function than the simplified
           one-size-fits-all operation of gamma32(). Diffusing the LEDs also
           really seems to help when using low-saturation colors.
*/
uint32_t Adafruit_NeoPixel::ColorHSV(uint16_t hue, uint8_t sat, uint8_t val) {

  uint8_t r, g, b;

  // Remap 0-65535 to 0-1529. Pure red is CENTERED on the 64K rollover;
  // 0 is not the start of pure red, but the midpoint...a few values above
  // zero and a few below 65536 all yield pure red (similarly, 32768 is the
  // midpoint, not start, of pure cyan). The 8-bit RGB hexcone (256 values
  // each for red, green, blue) really only allows for 1530 distinct hues
  // (not 1536, more on that below), but the full unsigned 16-bit type was
  // chosen for hue so that one's code can easily handle a contiguous color
  // wheel by allowing hue to roll over in either direction.
  hue = (hue * 1530L + 32768) / 65536;
  // Because red is centered on the rollover point (the +32768 above,
  // essentially a fixed-point +0.5), the above actually yields 0 to 1530,
  // where 0 and 1530 would yield the same thing. Rather than apply a
  // costly modulo operator, 1530 is handled as a special case below.

  // So you'd think that the color "hexcone" (the thing that ramps from
  // pure red, to pure yellow, to pure green and so forth back to red,
  // yielding six slices), and with each color component having 256
  // possible values (0-255), might have 1536 possible items (6*256),
  // but in reality there's 1530. This is because the last element in
  // each 256-element slice is equal to the first element of the next
  // slice, and keeping those in there this would create small
  // discontinuities in the color wheel. So the last element of each
  // slice is dropped...we regard only elements 0-254, with item 255
  // being picked up as element 0 of the next slice. Like this:
  // Red to not-quite-pure-yellow is:        255,   0, 0 to 255, 254,   0
  // Pure yellow to not-quite-pure-green is: 255, 255, 0 to   1, 255,   0
  // Pure green to not-quite-pure-cyan is:     0, 255, 0 to   0, 255, 254
  // and so forth. Hence, 1530 distinct hues (0 to 1529), and hence why
  // the constants below are not the multiples of 256 you might expect.

  // Convert hue to R,G,B (nested ifs faster than divide+mod+switch):
  if (hue < 510) { // Red to Green-1
    b = 0;
    if (hue < 255) { //   Red to Yellow-1
      r = 255;
      g = hue;       //     g = 0 to 254
    } else {         //   Yellow to Green-1
      r = 510 - hue; //     r = 255 to 1
      g = 255;
    }
  } else if (hue < 1020) { // Green to Blue-1
    r = 0;
    if (hue < 765) { //   Green to Cyan-1
      g = 255;
      b = hue - 510;  //     b = 0 to 254
    } else {          //   Cyan to Blue-1
      g = 1020 - hue; //     g = 255 to 1
      b = 255;
    }
  } else if (hue < 1530) { // Blue to Red-1
    g = 0;
    if (hue < 1275) { //   Blue to Magenta-1
      r = hue - 1020; //     r = 0 to 254
      b = 255;
    } else { //   Magenta to Red-1
      r = 255;
      b = 1530 - hue; //     b = 255 to 1
    }
  } else { // Last 0.5 Red (quicker than % operator)
    r = 255;
    g = b = 0;
  }

  // Apply saturation and value to R,G,B, pack into 32-bit result:
  uint32_t v1 = 1 + val;  // 1 to 256; allows >>8 instead of /255
  uint16_t s1 = 1 + sat;  // 1 to 256; same reason
  uint8_t s2 = 255 - sat; // 255 to 0
  return ((((((r * s1) >> 8) + s2) * v1) & 0xff00) << 8) |
         (((((g * s1) >> 8) + s2) * v1) & 0xff00) |
         (((((b * s1) >> 8) + s2) * v1) >> 8);
}

/*!
  @brief   Query the color of a previously-set pixel.
  @param   n  Index of pixel to read (0 = first).
  @return  'Packed' 32-bit RGB or WRGB value. Most significant byte is white
           (for RGBW pixels) or 0 (for RGB pixels), next is red, then green,
           and least significant byte is blue.
  @note    If the strip brightness has been changed from the default value
           of 255, the color read from a pixel may not exactly match what
           was previously written with one of the setPixelColor() functions.
           This gets more pronounced at lower brightness levels.
*/
uint32_t Adafruit_NeoPixel::getPixelColor(uint16_t n) const {
  if (n >= numLEDs)
    return 0; // Out of bounds, return no color.

  uint8_t *p;

  if (wOffset == rOffset) { // Is RGB-type device
    p = &pixels[n * 3];
    if (brightness) {
      // Stored color was decimated by setBrightness(). Returned value
      // attempts to scale back to an approximation of the original 24-bit
      // value used when setting the pixel color, but there will always be
      // some error -- those bits are simply gone. Issue is most
      // pronounced at low brightness levels.
      return (((uint32_t)(p[rOffset] << 8) / brightness) << 16) |
             (((uint32_t)(p[gOffset] << 8) / brightness) << 8) |
             ((uint32_t)(p[bOffset] << 8) / brightness);
    } else {
      // No brightness adjustment has been made -- return 'raw' color
      return ((uint32_t)p[rOffset] << 16) | ((uint32_t)p[gOffset] << 8) |
             (uint32_t)p[bOffset];
    }
  } else { // Is RGBW-type device
    p = &pixels[n * 4];
    if (brightness) { // Return scaled color
      return (((uint32_t)(p[wOffset] << 8) / brightness) << 24) |
             (((uint32_t)(p[rOffset] << 8) / brightness) << 16) |
             (((uint32_t)(p[gOffset] << 8) / brightness) << 8) |
             ((uint32_t)(p[bOffset] << 8) / brightness);
    } else { // Return raw color
      return ((uint32_t)p[wOffset] << 24) | ((uint32_t)p[rOffset] << 16) |
             ((uint32_t)p[gOffset] << 8) | (uint32_t)p[bOffset];
    }
  }
}

/*!
  @brief   Adjust output brightness. Does not immediately affect what's
           currently displayed on the LEDs. The next call to show() will
           refresh the LEDs at this level.
  @param   b  Brightness setting, 0=minimum (off), 255=brightest.
  @note    This was intended for one-time use in one's setup() function,
           not as an animation effect in itself. Because of the way this
           library "pre-multiplies" LED colors in RAM, changing the
           brightness is often a "lossy" operation -- what you write to
           pixels isn't necessary the same as what you'll read back.
           Repeated brightness changes using this function exacerbate the
           problem. Smart programs therefore treat the strip as a
           write-only resource, maintaining their own state to render each
           frame of an animation, not relying on read-modify-write.
*/
void Adafruit_NeoPixel::setBrightness(uint8_t b) {
  // Stored brightness value is different than what's passed.
  // This simplifies the actual scaling math later, allowing a fast
  // 8x8-bit multiply and taking the MSB. 'brightness' is a uint8_t,
  // adding 1 here may (intentionally) roll over...so 0 = max brightness
  // (color values are interpreted literally; no scaling), 1 = min
  // brightness (off), 255 = just below max brightness.
  uint8_t newBrightness = b + 1;
  if (newBrightness != brightness) { // Compare against prior value
    // Brightness has changed -- re-scale existing data in RAM,
    // This process is potentially "lossy," especially when increasing
    // brightness. The tight timing in the WS2811/WS2812 code means there
    // aren't enough free cycles to perform this scaling on the fly as data
    // is issued. So we make a pass through the existing color data in RAM
    // and scale it (subsequent graphics commands also work at this
    // brightness level). If there's a significant step up in brightness,
    // the limited number of steps (quantization) in the old data will be
    // quite visible in the re-scaled version. For a non-destructive
    // change, you'll need to re-render the full strip data. C'est la vie.
    uint8_t c, *ptr = pixels,
               oldBrightness = brightness - 1; // De-wrap old brightness value
    uint16_t scale;
    if (oldBrightness == 0)
      scale = 0; // Avoid /0
    else if (b == 255)
      scale = 65535 / oldBrightness;
    else
      scale = (((uint16_t)newBrightness << 8) - 1) / oldBrightness;
    for (uint16_t i = 0; i < numBytes; i++) {
      c = *ptr;
      *ptr++ = (c * scale) >> 8;
    }
    brightness = newBrightness;
  }
}

/*!
  @brief   Retrieve the last-set brightness value for the strip.
  @return  Brightness value: 0 = minimum (off), 255 = maximum.
*/
uint8_t Adafruit_NeoPixel::getBrightness(void) const { return brightness - 1; }

/*!
  @brief   Fill the whole NeoPixel strip with 0 / black / off.
*/
void Adafruit_NeoPixel::clear(void) { memset(pixels, 0, numBytes); }

// A 32-bit variant of gamma8() that applies the same function
// to all components of a packed RGB or WRGB value.
uint32_t Adafruit_NeoPixel::gamma32(uint32_t x) {
  uint8_t *y = (uint8_t *)&x;
  // All four bytes of a 32-bit value are filtered even if RGB (not WRGB),
  // to avoid a bunch of shifting and masking that would be necessary for
  // properly handling different endianisms (and each byte is a fairly
  // trivial operation, so it might not even be wasting cycles vs a check
  // and branch for the RGB case). In theory this might cause trouble *if*
  // someone's storing information in the unused most significant byte
  // of an RGB value, but this seems exceedingly rare and if it's
  // encountered in reality they can mask values going in or coming out.
  for (uint8_t i = 0; i < 4; i++)
    y[i] = gamma8(y[i]);
  return x; // Packed 32-bit return
}

/*!
  @brief   Fill NeoPixel strip with one or more cycles of hues.
           Everyone loves the rainbow swirl so much, now it's canon!
  @param   first_hue   Hue of first pixel, 0-65535, representing one full
                       cycle of the color wheel. Each subsequent pixel will
                       be offset to complete one or more cycles over the
                       length of the strip.
  @param   reps        Number of cycles of the color wheel over the length
                       of the strip. Default is 1. Negative values can be
                       used to reverse the hue order.
  @param   saturation  Saturation (optional), 0-255 = gray to pure hue,
                       default = 255.
  @param   brightness  Brightness/value (optional), 0-255 = off to max,
                       default = 255. This is distinct and in combination
                       with any configured global strip brightness.
  @param   gammify     If true (default), apply gamma correction to colors
                       for better appearance.
*/
void Adafruit_NeoPixel::rainbow(uint16_t first_hue, int8_t reps,
  uint8_t saturation, uint8_t brightness, bool gammify) {
  for (uint16_t i=0; i<numLEDs; i++) {
    uint16_t hue = first_hue + (i * reps * 65536) / numLEDs;
    uint32_t color = ColorHSV(hue, saturation, brightness);
    if (gammify) color = gamma32(color);
    setPixelColor(i, color);
  }
}

/*!
  @brief  Convert pixel color order from string (e.g. "BGR") to NeoPixel
          color order constant (e.g. NEO_BGR). This may be helpful for code
          that initializes from text configuration rather than compile-time
          constants.
  @param   v  Input string. Should be reasonably sanitized (a 3- or 4-
              character NUL-terminated string) or undefined behavior may
              result (output is still a valid NeoPixel order constant, but
              might not present as expected). Garbage in, garbage out.
  @return  One of the NeoPixel color order constants (e.g. NEO_BGR).
           NEO_KHZ400 or NEO_KHZ800 bits are not included, nor needed (all
           NeoPixels actually support 800 KHz it's been found, and this is
           the default state if no KHZ bits set).
  @note    This function is declared static in the class so it can be called
           without a NeoPixel object (since it's not likely been declared
           in the code yet). Use Adafruit_NeoPixel::str2order().
*/
neoPixelType Adafruit_NeoPixel::str2order(const char *v) {
  int8_t r = 0, g = 0, b = 0, w = -1;
  if (v) {
    char c;
    for (uint8_t i=0; ((c = tolower(v[i]))); i++) {
      if (c == 'r') r = i;
      else if (c == 'g') g = i;
      else if (c == 'b') b = i;
      else if (c == 'w') w = i;
    }
    r &= 3;
  }
  if (w < 0) w = r; // If 'w' not specified, duplicate r bits
  return (w << 6) | (r << 4) | ((g & 3) << 2) | (b & 3);
} 

#endif // ADAFRUIT_NEOPIXEL_H
