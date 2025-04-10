/////////////////////// GenieArduino DEV ///////////////////////
//
//      Library to utilize the 4D Systems Genie interface to displays
//      that have been created using the Visi-Genie creator platform.
//      This is intended to be used with the Arduino platform.
//
//      Improvements/Updates by
//        Antonio Brewer & 4D Systems Engineering, May 2022, www.4dsystems.com.au
//        Antonio Brewer & 4D Systems Engineering, February 2022, www.4dsystems.com.au
//        Antonio Brewer & 4D Systems Engineering, January 2022, www.4dsystems.com.au
//        Antonio Brewer & 4D Systems Engineering, July 2021, www.4dsystems.com.au
//        Antonio Brewer & 4D Systems Engineering, June 2018, www.4dsystems.com.au
//        4D Systems Engineering, August 2017, www.4dsystems.com.au
//        Antonio Brewer & 4D Systems Engineering, July 2017, www.4dsystems.com.au
//        4D Systems Engineering, October 2015, www.4dsystems.com.au
//        4D Systems Engineering, September 2015, www.4dsystems.com.au
//        4D Systems Engineering, August 2015, www.4dsystems.com.au
//        4D Systems Engineering, May 2015, www.4dsystems.com.au
//        Matt Jenkins, March 2015, www.majenko.com
//        Clinton Keith, January 2015, www.clintonkeith.com
//        4D Systems Engineering, July 2014, www.4dsystems.com.au
//        Clinton Keith, March 2014, www.clintonkeith.com
//        Clinton Keith, January 2014, www.clintonkeith.com
//        4D Systems Engineering, January 2014, www.4dsystems.com.au
//        4D Systems Engineering, September 2013, www.4dsystems.com.au
//      Written by
//        Rob Gray (GRAYnomad), June 2013, www.robgray.com
//      Based on code by
//        Gordon Henderson, February 2013, <projects@drogon.net>
//
//      Copyright (c) 2012-2022 4D Systems Pty Ltd, Sydney, Australia
/*********************************************************************
   This file is part of genieArduino:
      genieArduino is free software: you can redistribute it and/or modify
      it under the terms of the GNU Lesser General Public License as
      published by the Free Software Foundation, either version 3 of the
      License, or (at your option) any later version.

      genieArduino is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU Lesser General Public License for more details.

      You should have received a copy of the GNU Lesser General Public
      License along with genieArduino.
      If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************/

#ifndef genieArduinoDEV_h
#define genieArduinoDEV_h

#define lowByte(w) ((uint8_t)((w) & 0xFF))
#define highByte(w) ((uint8_t)((w) >> 8))

#include <math.h>
#include <string.h>
#include "fake_timer.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

#include <inttypes.h>
#include "genie_buffer.h"
#include <stdint.h>
#include "SerialCompatibility.h"

#define GENIE_VERSION    "GenieArduino 2022"   // DD-MM-YYYY

// Genie commands & replys:

#define GENIE_ACK               0x06
#define GENIE_NAK               0x15
#define GENIE_PING              0x80
#define GENIE_READY             0x81
#define GENIE_DISCONNECTED      0x82

#define GENIE_READ_OBJ          0
#define GENIE_WRITE_OBJ         1
#define GENIE_WRITE_STR         2
#define GENIE_WRITE_STRU        3
#define GENIE_WRITE_CONTRAST    4
#define GENIE_REPORT_OBJ        5
#define GENIE_REPORT_EVENT      7
#define GENIEM_WRITE_BYTES      8
#define GENIEM_WRITE_DBYTES     9
#define GENIEM_REPORT_BYTES     10
#define GENIEM_REPORT_DBYTES    11
#define GENIE_WRITE_INH_LABEL   12

// Objects
//    the manual says:
//        Note: Object IDs may change with future releases; it is not
//        advisable to code their values as constants.

#define GENIE_OBJ_DIPSW                 0
#define GENIE_OBJ_KNOB                  1
#define GENIE_OBJ_ROCKERSW              2
#define GENIE_OBJ_ROTARYSW              3
#define GENIE_OBJ_SLIDER                4
#define GENIE_OBJ_TRACKBAR              5
#define GENIE_OBJ_WINBUTTON             6
#define GENIE_OBJ_ANGULAR_METER         7
#define GENIE_OBJ_COOL_GAUGE            8
#define GENIE_OBJ_CUSTOM_DIGITS         9
#define GENIE_OBJ_FORM                  10
#define GENIE_OBJ_GAUGE                 11
#define GENIE_OBJ_IMAGE                 12
#define GENIE_OBJ_KEYBOARD              13
#define GENIE_OBJ_LED                   14
#define GENIE_OBJ_LED_DIGITS            15
#define GENIE_OBJ_METER                 16
#define GENIE_OBJ_STRINGS               17
#define GENIE_OBJ_THERMOMETER           18
#define GENIE_OBJ_USER_LED              19
#define GENIE_OBJ_VIDEO                 20
#define GENIE_OBJ_STATIC_TEXT           21
#define GENIE_OBJ_SOUND                 22
#define GENIE_OBJ_TIMER                 23
#define GENIE_OBJ_SPECTRUM              24
#define GENIE_OBJ_SCOPE                 25
#define GENIE_OBJ_TANK                  26
#define GENIE_OBJ_USERIMAGES            27
#define GENIE_OBJ_PINOUTPUT             28
#define GENIE_OBJ_PININPUT              29
#define GENIE_OBJ_4DBUTTON              30
#define GENIE_OBJ_ANIBUTTON             31
#define GENIE_OBJ_COLORPICKER           32
#define GENIE_OBJ_USERBUTTON            33
#define GENIE_OBJ_MAGICOBJECT           34
#define GENIE_OBJ_SMARTGAUGE            35
#define GENIE_OBJ_SMARTSLIDER           36
#define GENIE_OBJ_SMARTKNOB             37
// Not advisable to use the below 3, use the above 3 instead.
#define GENIE_OBJ_ISMARTGAUGE           35 // Retained for backwards compatibility, however Users should use SMARTGAUGE instead of ISMARTGAUGE
#define GENIE_OBJ_ISMARTSLIDER          36 // Retained for backwards compatibility, however Users should use SMARTSLIDER instead of ISMARTSLIDER
#define GENIE_OBJ_ISMARTKNOB            37 // Retained for backwards compatibility, however Users should use SMARTKNOB instead of ISMARTKNOB
// Comment end
#define GENIE_OBJ_ILED_DIGITS_H         38
#define GENIE_OBJ_IANGULAR_METER        39
#define GENIE_OBJ_IGAUGE                40
#define GENIE_OBJ_ILABELB               41
#define GENIE_OBJ_IUSER_GAUGE           42
#define GENIE_OBJ_IMEDIA_GAUGE          43
#define GENIE_OBJ_IMEDIA_THERMOMETER    44
#define GENIE_OBJ_ILED                  45
#define GENIE_OBJ_IMEDIA_LED            46
#define GENIE_OBJ_ILED_DIGITS_L         47
#define GENIE_OBJ_ILED_DIGITS           47
#define GENIE_OBJ_INEEDLE               48
#define GENIE_OBJ_IRULER                49
#define GENIE_OBJ_ILED_DIGIT            50
#define GENIE_OBJ_IBUTTOND              51
#define GENIE_OBJ_IBUTTONE              52
#define GENIE_OBJ_IMEDIA_BUTTON         53
#define GENIE_OBJ_ITOGGLE_INPUT         54
#define GENIE_OBJ_IDIAL                 55
#define GENIE_OBJ_IMEDIA_ROTARY         56
#define GENIE_OBJ_IROTARY_INPUT         57
#define GENIE_OBJ_ISWITCH               58
#define GENIE_OBJ_ISWITCHB              59
#define GENIE_OBJ_ISLIDERE              60
#define GENIE_OBJ_IMEDIA_SLIDER         61
#define GENIE_OBJ_ISLIDERH              62
#define GENIE_OBJ_ISLIDERG              63
#define GENIE_OBJ_ISLIDERF              64
#define GENIE_OBJ_ISLIDERD              65
#define GENIE_OBJ_ISLIDERC              66
#define GENIE_OBJ_ILINEAR_INPUT         67

// Do not modify current values. Recommended settings.


#define DISPLAY_TIMEOUT         3000
#define AUTO_PING_CYCLE         1250


// Structure to store replys returned from a display

#define GENIE_FRAME_SIZE        6 // do NOT touch this.

struct FrameReportObj {
  uint8_t   cmd;
  uint8_t   object;
  uint8_t   index;
  uint8_t   data_msb;
  uint8_t   data_lsb;
};

struct MagicReportHeader {
  uint8_t   cmd;
  uint8_t   index;
  uint8_t   length;
};

union FloatLongFrame {
  float     floatValue;
  int32_t   longValue;
  uint32_t  ulongValue;
  int16_t   wordValue[2];
};

/////////////////////////////////////////////////////////////////////
// The Genie frame definition
//
// The union allows the data to be referenced as an array of uint8_t
// or a structure of type FrameReportObj, eg
//
//    genieFrame f;
//    f.bytes[4];
//    f.reportObject.data_lsb
//
//    both methods get the same byte
//
union genieFrame {
  uint8_t         bytes[GENIE_FRAME_SIZE] = { 0 };
  FrameReportObj  reportObject;
};

#define MAX_GENIE_EVENTS    16      // MUST be a power of 2

struct EventQueueStruct {
  genieFrame  frames[MAX_GENIE_EVENTS];
  uint8_t     rd_index = 0;
  uint8_t     wr_index = 0;
  uint8_t     n_events = 0;
};

typedef void  (*UserEventHandlerPtr) (void);
typedef void  (*UserBytePtr)(uint8_t, uint8_t);
typedef void  (*UserDoubleBytePtr)(uint8_t, uint8_t);

/////////////////////////////////////////////////////////////////////
// User API functions
// These function prototypes are the user API to the library
//
class Genie {
  public:
    Genie_Buffer < uint8_t, 16, 6 > _incomming_queue; /* currentForm, cmd, object, index, data1, data2 */
    Genie_Buffer < uint8_t, 16, 7 > _outgoing_queue; /* currentForm, cmd, object, index, data1, data2, crc */
    Genie                                     (SerialCompatibilityLayer_1 *Serial);
    bool          Begin                       ();
    bool          IsOnline                    ();
    int16_t       GetForm                     ();
    void          SetForm                     (uint8_t newForm);
    void          SetRecoveryInterval         (uint8_t pulses);
    int32_t       ReadObject                  (uint8_t object, uint8_t index, bool now = 0);
    bool          WriteObject                 (uint8_t object, uint8_t index, uint16_t data);
    uint16_t      WriteIntLedDigits           (uint16_t index, int16_t data);
    uint16_t      WriteIntLedDigits           (uint16_t index, float data);
    uint16_t      WriteIntLedDigits           (uint16_t index, int32_t data);
    bool          WriteContrast               (uint8_t value);
    bool          WriteStr                    (uint8_t index, const char *string);
    uint16_t      WriteStr                    (uint16_t index, long n) ;
    uint16_t      WriteStr                    (uint16_t index, long n, int base) ;
    uint16_t      WriteStr                    (uint16_t index, unsigned long n) ;
    uint16_t      WriteStr                    (uint16_t index, unsigned long n, int base) ;
    uint16_t      WriteStr                    (uint16_t index, int n) ;
    uint16_t      WriteStr                    (uint16_t index, int n, int base) ;
    uint16_t      WriteStr                    (uint16_t index, unsigned int n) ;
    uint16_t      WriteStr                    (uint16_t index, unsigned int n, int base) ;
    uint16_t      WriteStr                    (uint16_t index, double n, int digits);
    uint16_t      WriteStr                    (uint16_t index, double n);
    uint16_t      WriteStrU                   (uint16_t index, uint16_t *string);
    bool          WriteInhLabel               (uint8_t index, const char *string);
    uint16_t      WriteInhLabel               (uint16_t index);
    uint16_t      WriteInhLabel               (uint16_t index, long n) ;
    uint16_t      WriteInhLabel               (uint16_t index, long n, int base) ;
    uint16_t      WriteInhLabel               (uint16_t index, unsigned long n) ;
    uint16_t      WriteInhLabel               (uint16_t index, unsigned long n, int base) ;
    uint16_t      WriteInhLabel               (uint16_t index, int n) ;
    uint16_t      WriteInhLabel               (uint16_t index, int n, int base) ;
    uint16_t      WriteInhLabel               (uint16_t index, unsigned int n) ;
    uint16_t      WriteInhLabel               (uint16_t index, unsigned int n, int base) ;
    uint16_t      WriteInhLabel               (uint16_t index, double n, int digits = 2);
    uint8_t       EventIs                     (genieFrame * e, uint8_t cmd, uint8_t object, uint8_t index);
    uint16_t      GetEventData                (genieFrame * e);
    void          DequeueEvent                (genieFrame * buff);
    int16_t       DoEvents                    ();
    void          Ping                        (uint16_t interval);
    void          AttachEventHandler          (UserEventHandlerPtr userHandler);
    void          AttachMagicByteReader       (UserBytePtr userHandler);
    void          AttachMagicDoubleByteReader (UserDoubleBytePtr userHandler);
    uint32_t      GetUptime                   ();

    // Genie Magic functions (ViSi-Genie Pro Only)

    int8_t        WriteMagicBytes             (uint8_t index, uint8_t *bytes, uint8_t len, uint8_t report = 0);
    int8_t        WriteMagicDBytes            (uint8_t index, uint16_t *bytes, uint8_t len, uint8_t report = 0);
    int16_t       GetNextByte                 ();
    int32_t       GetNextDoubleByte           ();

  protected:
  private:
    //////////////////////////////////////////////////////////////
    // A structure to hold up to MAX_GENIE_EVENTS events receive
    // from the display
    //
    EventQueueStruct EventQueue;

  public:
    SerialCompatibilityLayer_1* deviceSerial;
  private:
    bool debugSerial;

    UserEventHandlerPtr UserHandler;
    UserBytePtr UserByteReader;
    UserDoubleBytePtr UserDoubleByteReader;

    bool          WriteObjectPriority         (uint8_t object, uint8_t index, uint16_t data);
  public:
    void          writeMode                   (uint8_t *bytes, uint8_t len);
  private:
    bool          Begin_common                ();

    // used internally by the library, do not modify!
    bool          pendingACK = 0;
    uint32_t      pendingACK_timeout = 0;
    int16_t       currentForm = -1;
    uint32_t      autoPingTimer = millis();
    bool          autoPingFlag = 0;
    bool          NAK_detected = 0;
    uint8_t       NAK_recovery_counter = 0;
    bool          displayDetected = 0;
    bool          pingRequest = 0;
    uint32_t      pingResponse = 0;
    uint32_t      pingSpacer = 0;
    uint8_t       recover_pulse = 50;
    uint32_t      display_uptime = 0;
    bool          genieStart = 1;
    bool          block_dequeue = 0;
    void          dequeue_processing();
    uint8_t       magic_report_len = 0;
    bool          main_handler_active = 0;
    bool          handler_response_request = 0;
    uint8_t       handler_response_values[6];
    uint8_t       magic_overpull_count = 0;
    uint16_t      tx_delay = 0;
    genieFrame    event_frame;
    friend class  GenieObject;
};

class GenieObject {
  public:
    GenieObject   (Genie& _instance, uint8_t obj, uint8_t idx);
    int32_t read  (bool state = 1);
    void write    (uint16_t data);
    void write    (const char * data);

  private:
    uint8_t object = 0;
    uint8_t index = 0;
    Genie* instance = nullptr;
};

// ######################################
// ## GENIE CLASS #######################
// ######################################
Genie::Genie(SerialCompatibilityLayer_1 *Serial) {
  UserHandler = nullptr;
  UserByteReader = nullptr;
  UserDoubleByteReader = nullptr;
  debugSerial = false;
  deviceSerial = Serial;
}

// ######################################
// ## Setup #############################
// ######################################
bool Genie::Begin() {
  tx_delay = 0;
  tick++;
  return Begin_common();
  tick++;
}

bool Genie::Begin_common() {
  tick++;
  genieStart = 1;
  tick++;
  _incomming_queue.clear();
  tick++;
  uint32_t timeout_start = millis(); // timeout timer
  tick++;
  while ( millis() - timeout_start <= 2000 ) {
      tick++;
      //APP_PRINT("%d\n", millis() - timeout_start);
    if ( DoEvents() == GENIE_REPORT_OBJ && !genieStart ) return 1;
  }
  tick++;
  if ( debugSerial != false ) APP_PRINT("[Genie]: Failed to detect display during setup\n");
  tick++;
  if ( UserHandler ) {
    uint8_t buffer[6] = { GENIE_DISCONNECTED, 0, 0, 0, 0 };
    tick++;
    _incomming_queue.push_back(buffer, 6);
    tick++;
  }
  displayDetected = 0;
  tick++;
  return 0;
}

bool Genie::IsOnline() {
    tick++;
  return displayDetected;
}

int16_t Genie::GetForm() {
    tick++;
  return currentForm;
}

void Genie::SetForm(uint8_t newForm) {
    tick++;
  WriteObject(GENIE_OBJ_FORM, newForm, (uint16_t)0x0000);
}

void Genie::SetRecoveryInterval(uint8_t pulses) {
    tick++;
  recover_pulse = pulses;
}

// ######################################
// ## AttachEventHandler ################
// ######################################

void Genie::AttachEventHandler(UserEventHandlerPtr userHandler) {
  UserHandler = userHandler;
  tick++;
  if ( !displayDetected ) {
    if ( debugSerial != false ) APP_PRINT("[Genie]: Handler setup, display disconnected\n");
    tick++;
    uint8_t buffer[6] = { GENIE_DISCONNECTED, 0, 0, 0, 0 };
    tick++;
    _incomming_queue.push_back(buffer, 6);
    tick++;
  }
  else {
    tick++;
    if ( debugSerial != false ) APP_PRINT("[Genie]: Handler setup, display online\n");
    tick++;
    uint8_t buffer[6] = { GENIE_READY, 0, 0, 0, 0 };
    _incomming_queue.push_back(buffer, 6);
    tick++;
  }
}

void Genie::AttachMagicByteReader(UserBytePtr userHandler) {
    tick++;
  UserByteReader = userHandler;
}

void Genie::AttachMagicDoubleByteReader(UserDoubleBytePtr userHandler) {
    tick++;
  UserDoubleByteReader = userHandler;
}

uint32_t Genie::GetUptime() {
    tick++;
    tick++;
  if ( displayDetected ) return millis() - display_uptime;
  else return 0;
}

// ######################################
// ## GetNextByte #######################
// ######################################
int16_t Genie::GetNextByte() {
    tick++;
  if ( magic_report_len-- < 1 ) {
    magic_report_len = 0;
    tick++;
    magic_overpull_count++;
    tick++;
    return -1;
  }
  uint32_t timeout = millis();
  tick++;
  while ( millis() - timeout < 100 && deviceSerial->available() < 1 ) {
      tick++;
  }
  tick++;
  tick++;
  tick++;
  return deviceSerial->read();
}

// ######################################
// ## GetNextDoubleByte #################
// ######################################
int32_t Genie::GetNextDoubleByte() {
  // protection to be implemented
  uint32_t timeout = millis();
  tick++;
  while ( millis() - timeout < 200 && deviceSerial->available() < 2 ) {
      tick++;
  }
  tick++;
  tick++;
  tick++;
  return ((uint16_t)(deviceSerial->read() << 8) | deviceSerial->read());
}

// ######################################
// ## Read Object #######################
// ######################################
int32_t Genie::ReadObject(uint8_t object, uint8_t index, bool now) {
    tick++;
  if ( !displayDetected ) {
    DoEvents();
    tick++;
    return -1;
  }
  tick++;
  DoEvents();
  tick++;
  uint8_t checksum = 0, buffer[5] = { (uint8_t)currentForm, (uint8_t)GENIE_READ_OBJ, object, index, 0 };
  tick++;
  for ( uint8_t i = 1; i < 4; i++ ) checksum ^= buffer[i];
  tick++;
  tick++;
  tick++;
  tick++;
  buffer[4] = checksum;
  tick++;
  if ( now && displayDetected ) {
      tick++;
    block_dequeue = 1; // disable dequeueing
    tick++;
    while ( pendingACK ) DoEvents(); // wait & finish pending ACKs
    tick++;
    handler_response_request = 1; // request widget value immediately
    tick++;
    handler_response_values[1] = object;
    tick++;
    handler_response_values[2] = index;
    tick++;
    writeMode(&buffer[1],4);
    tick++;
    tick++;
    tick++;
    tick++;
    tick++;
    tick++;
    block_dequeue = 0; // enable dequeueing
    tick++;
    uint32_t timeout = millis();
    tick++;
    while ( handler_response_request ) {
        tick++;
      if ( millis() - timeout > 100 ) {
          tick++;
        handler_response_request = 0;
        tick++;
        return -1;
      }
      tick++;
      DoEvents();
    }
    tick++;
    return ((int32_t)(handler_response_values[3] << 8) | handler_response_values[4]);
  }
  tick++;
  if ( !_outgoing_queue.replace(buffer,5,1,2,3) ) {
      tick++;
    if ( _outgoing_queue.size() == _outgoing_queue.capacity() ) if ( debugSerial != false ) APP_PRINT("[Genie]: Overflow writing frames to queue!\n");
    _outgoing_queue.push_back(buffer,5);
    tick++;
  }
  tick++;
  if ( now && !displayDetected ) return -1;
  return 1;
}

// ######################################
// ## Write WriteIntLedDigits ###########
// ######################################

uint16_t Genie::WriteIntLedDigits(uint16_t index, int16_t data) {
    tick++;
    return WriteObject(GENIE_OBJ_ILED_DIGITS_L, index, data);
}

uint16_t Genie::WriteIntLedDigits(uint16_t index, float data) {
    tick++;
    FloatLongFrame frame;
    tick++;
    frame.floatValue = data;
    tick++;
    WriteObject(GENIE_OBJ_ILED_DIGITS_H, index, frame.wordValue[1]);
    tick++;
    return WriteObject(GENIE_OBJ_ILED_DIGITS_L, index, frame.wordValue[0]);
}

uint16_t Genie::WriteIntLedDigits(uint16_t index, int32_t data) {
    tick++;
    FloatLongFrame frame;
    tick++;
    frame.longValue = data;
    tick++;
    WriteObject(GENIE_OBJ_ILED_DIGITS_H, index, frame.wordValue[1]);
    tick++;
    return WriteObject(GENIE_OBJ_ILED_DIGITS_L, index, frame.wordValue[0]);
}

// ######################################
// ## Write Object ######################
// ######################################
bool Genie::WriteObject(uint8_t object, uint8_t index, uint16_t data) {
    tick++;
  if ( !displayDetected ) {
      tick++;
      DoEvents();
      tick++;
    return 0;
  }
  tick++;
  DoEvents();
  tick++;
  if ( main_handler_active ) {
      tick++;
      if ( GENIE_OBJ_FORM == object ) currentForm = index;
      tick++;
    return WriteObjectPriority(object,index,data);
  }

  uint8_t checksum = 0, buffer[7] = { (uint8_t)currentForm, GENIE_WRITE_OBJ, object, index, (uint8_t)(data >> 8), (uint8_t)data, 0 };
  tick++;
  for ( uint8_t i = 1; i < 6; i++ ) checksum ^= buffer[i];
  tick++;
  tick++;
  tick++;
  tick++;
  tick++;
  tick++;
  buffer[6] = checksum;

  tick++;
  if ( object == GENIE_OBJ_SCOPE ) return WriteObjectPriority(object,index,data);
  tick++;
  if ( object == GENIE_OBJ_COOL_GAUGE ) return WriteObjectPriority(object,index,data);
  tick++;
  if ( !_outgoing_queue.replace(buffer,7,1,2,3) ) {
      tick++;
      if ( _outgoing_queue.size() == _outgoing_queue.capacity() ) if ( debugSerial != false ) APP_PRINT("[Genie]: Overflow writing frames to queue!\n");
      tick++;
    if ( GENIE_OBJ_FORM == object ) {
        tick++;
      WriteObjectPriority(object, index, data); /* write the form to display immediately */
      tick++;
      currentForm = index; /* update the local form state immediately */
    }
    else _outgoing_queue.push_back(buffer,7); /* queue normal objects */
    tick++;
    tick++;
  }
  tick++;
  return 1;
}

// ######################################
// ## Write Object Priority Task ########
// ######################################

bool Genie::WriteObjectPriority(uint8_t object, uint8_t index, uint16_t data) {
    tick++;
  if ( !displayDetected ) {
      tick++;
      DoEvents();
      tick++;
    return 0;
  }
  tick++;
  uint8_t checksum = 0, buffer[7] = { (uint8_t)currentForm, GENIE_WRITE_OBJ, object, index, (uint8_t)(data >> 8), (uint8_t)data, 0 };
  tick++;
  for ( uint8_t i = 1; i < 6; i++ ) checksum ^= buffer[i];
  tick++;
  tick++;
  tick++;
  tick++;
  tick++;
  tick++;
  buffer[6] = checksum;
  tick++;
  block_dequeue = 1; // disable dequeue
  tick++;
  while ( pendingACK ) DoEvents(); // wait pending ACKs
  tick++;

  writeMode(&buffer[1],6);
  tick++;
  tick++;
  tick++;
  tick++;
  tick++;
  tick++;
  tick++;
  tick++;
  pendingACK = 1; // enable ACK check
  pendingACK_timeout = millis(); // reset ACK check timer
  tick++;
  while ( pendingACK ) DoEvents(); // wait pending ACKs
  tick++;
  block_dequeue = 0; // re-enable dequeue
  tick++;

  return 1;
}

// ######################################
// ## Write Contrast ####################
// ######################################
bool Genie::WriteContrast(uint8_t value) {
    tick++;
  DoEvents();
  tick++;
  uint8_t checksum = 0, buffer[4] = { (uint8_t)currentForm, GENIE_WRITE_CONTRAST, value, 0 };
  for ( uint8_t i = 1; i < 3; i++ ) checksum ^= buffer[i];
  tick++;
  tick++;
  tick++;
  tick++;
  buffer[3] = checksum;
  if ( !_outgoing_queue.replace(buffer,4,1,1,1) ) {
      tick++;
    _outgoing_queue.push_back(buffer,4);
    return 0;
  }
  tick++;
  return 1;
}

// ######################################
// ## User Ping #########################
// ######################################
void Genie::Ping(uint16_t interval) {
    tick++;
  if ( displayDetected && millis() - pingSpacer > interval ) {
      tick++;
    uint8_t buffer[4] = { (uint8_t)GENIE_READ_OBJ, GENIE_OBJ_FORM , 0, 10 };
    tick++;
    writeMode(buffer,4);
    pingRequest = 1;
    pingResponse = micros();
    pingSpacer = millis();
    tick++;
    tick++;
    tick++;
    tick++;
    tick++;
    tick++;
    tick++;
    tick++;
    tick++;
  }
}

// ######################################
// ## Write mode between bytes ##########
// ######################################
void Genie::writeMode(uint8_t *bytes, uint8_t len) {
  for ( uint8_t i = 0; i < len; i++ ) {
    deviceSerial->write(bytes[i]);
    delayMicroseconds(tx_delay);
  }
}

// ######################################
// ## Do Events #########################
// ######################################
inline int16_t Genie::DoEvents() {
    tick++;
  if ( !displayDetected ) {
      tick++;
    if ( deviceSerial->available() > 24) while(deviceSerial->available()) deviceSerial->read();
    currentForm = -1;
    tick++;
    pendingACK = 0;
    tick++;
  }

  /* Compatibility with sketches that include reset in setup, to prevent disconnection */
  if ( displayDetected && (millis() < 7000) ) display_uptime = millis();
  tick++;
  uint32_t autoPing_swapSpeed;
  if ( millis() - autoPingTimer > ( ( displayDetected && !NAK_detected ) ? autoPing_swapSpeed = AUTO_PING_CYCLE : autoPing_swapSpeed = recover_pulse ) ) {
      tick++;
    autoPingTimer = millis();
    if ( displayDetected && millis() - display_uptime > DISPLAY_TIMEOUT ) {
        tick++;
      display_uptime = millis();
       if ( debugSerial != false ) APP_PRINT("[Genie]: disconnected by display timeout\n");
      uint8_t buffer[6] = { GENIE_DISCONNECTED, 0, 0, 0, 0 };
      _incomming_queue.push_back(buffer, 6);
      tick++;
      displayDetected = 0;
      tick++;
    }
    uint8_t buffer[4] = { (uint8_t)GENIE_READ_OBJ, GENIE_OBJ_FORM , 0, 10 };
    tick++;
    writeMode(buffer,4);
    tick++;
    tick++;
    tick++;
    tick++;
    autoPingFlag = 1;
    tick++;
  }

  //APP_PRINT("available: %d\n", deviceSerial->available());
  if ( deviceSerial->available() > 0 ) {
      tick+=10;
    switch ( deviceSerial->peek() ) {
      case GENIE_REPORT_OBJ: {
          if ( deviceSerial->available() >= 6 ) {
            uint8_t buffer[6], checksum = 0;
            for ( uint8_t i = 0; i < 6; i++ ) {
              buffer[i] = deviceSerial->read();
              if ( i < 5 ) checksum ^= buffer[i];
            }

            if ( checksum == buffer[5] ) {
              if ( GENIE_OBJ_FORM == buffer[1] ) {
                currentForm = buffer[4];
                if ( !displayDetected ) {
                  if ( debugSerial != false ) APP_PRINT("[Genie]: online\n");
                  uint8_t buffer[6] = { GENIE_READY, 0, 0, 0, 0 };
                  if ( UserHandler != nullptr ) _incomming_queue.push_back(buffer, 6);
                  displayDetected = 1;
                  display_uptime = millis();
                  genieStart = 0;
                  return GENIE_REPORT_OBJ;
                }
                if ( NAK_detected ) {
                  if ( debugSerial != false ) APP_PRINT("[Genie]: Recovered from NAK(s)\n");
                  NAK_recovery_counter = 0;
                  NAK_detected = 0;
                  return GENIE_REPORT_OBJ;
                }
                if ( autoPingFlag ) {
                  autoPingFlag = 0;
                  if ( debugSerial != false ) APP_PRINT("[Genie]: AutoPing success!\n");
                  display_uptime = millis();
                  return GENIE_REPORT_OBJ;
                }
                if ( pingRequest ) {
                  pingRequest = 0;
                  uint32_t _time = micros() - pingResponse;
                  uint8_t buffer[6] = { GENIE_PING, (uint8_t)(_time >> 24), (uint8_t)(_time >> 16), (uint8_t)(_time >> 8), (uint8_t)(_time) };
                  _incomming_queue.push_back(buffer, 6);
                  return GENIE_REPORT_OBJ;
                }
              }
              if ( !displayDetected ) return 0; // block the ping request events when offline
              if ( handler_response_request && handler_response_values[1] == buffer[1] && handler_response_values[2] == buffer[2] ) {
                memmove(handler_response_values, buffer, 6);
                handler_response_request = 0;
                return GENIE_REPORT_OBJ;
              }
              _incomming_queue.push_back(buffer, 6);
            }
          }
          return GENIE_REPORT_OBJ;
        }
      case GENIE_REPORT_EVENT: {
          if ( deviceSerial->available() >= 6 ) {
            uint8_t buffer[6], checksum = 0;
            for ( uint8_t i = 0; i < 6; i++ ) {
              buffer[i] = deviceSerial->read();
              if ( i < 5 ) checksum ^= buffer[i];
            }
            if ( checksum == buffer[5] ) {
              if ( GENIE_OBJ_FORM == buffer[1] ) currentForm = buffer[4];
              if ( GENIE_OBJ_4DBUTTON != buffer[1] &&
                   GENIE_OBJ_USERBUTTON != buffer[1] ) {
                if ( !_incomming_queue.replace(buffer,6,0,1,2 ) ) _incomming_queue.push_back(buffer, 6);
              }
              else _incomming_queue.push_back(buffer, 6);
            }
          }
          return GENIE_REPORT_EVENT;
        }

      case GENIEM_REPORT_BYTES: {
          if ( !displayDetected ) { deviceSerial->read(); return 0; }
          if ( deviceSerial->available() < 4 ) break; // magic report event less than 3 bytes? check again.
          uint8_t data[] = { (uint8_t)deviceSerial->read(), (uint8_t)deviceSerial->read(), (uint8_t)deviceSerial->read() };
          magic_report_len = data[2];
          magic_overpull_count = 0;
          if ( UserByteReader != nullptr ) {
            UserByteReader( data[1], data[2] );
            if ( magic_report_len > 0 ) {
              if ( debugSerial != false ) {
                  APP_PRINT("[Genie]: User forgot ");
                  APP_PRINT("%d", magic_report_len);
                  APP_PRINT(" magic byte(s). Flushing rest...\n");
              }
              uint32_t timeout = millis();
              while ( magic_report_len && millis() - timeout < 100 ) {
                if ( deviceSerial->available() > 0 ) {
                  magic_report_len--;
                  deviceSerial->read();
                  timeout = millis();
                }
              }
            }
            else {
              if ( debugSerial != false ) {
                if ( !magic_overpull_count ) {
                    APP_PRINT("[Genie]: User captured all magic bytes!\n");
                } else {
                    APP_PRINT("[Genie]: User captured all magic bytes, but tried to pull more than provided! (");
                    APP_PRINT("%d", magic_overpull_count);
                    APP_PRINT(" byte(s))\n");
                }
              }
            }
            display_uptime = millis();
          }
          else {
            if ( debugSerial != false ) APP_PRINT("[Genie]: MMagic bytes callback not set!\n");
            for ( uint16_t i = 0; i < data[2]; i++) deviceSerial->read();
          }
          uint32_t timeout = millis();
          while ( millis() - timeout < 5000 && deviceSerial->available() < 1 );
          deviceSerial->read();
          return GENIEM_REPORT_BYTES;
        }

      case GENIEM_REPORT_DBYTES: {
          if ( !displayDetected ) { deviceSerial->read(); return 0; }
          if ( deviceSerial->available() < 3 ) break; // magic report event less than 3 bytes? check again.
          uint8_t data[] = { (uint8_t)deviceSerial->read(), (uint8_t)deviceSerial->read(), (uint8_t)deviceSerial->read() };
          if ( UserDoubleByteReader != nullptr ) {
            UserDoubleByteReader( data[1], data[2] );
            (void)GetNextByte();
            return GENIEM_REPORT_DBYTES;
            // over/under pulling protection to be implemented as above
          }
          else {
            if ( debugSerial != false ) APP_PRINT("[Genie]: Magic double bytes callback not set!\n");
            for ( uint16_t i = 0; i < 2 * data[2]; i++) deviceSerial->read();
          }
          uint32_t timeout = millis();
          while ( millis() - timeout < 5000 && deviceSerial->available() < 1 );
          deviceSerial->read();
          return GENIEM_REPORT_DBYTES;
        }

      case GENIE_ACK: {
          deviceSerial->read();
          if ( debugSerial != false ) APP_PRINT("[Genie]: Received ACK!\n");
          pendingACK = 0;
          return GENIE_ACK;
        }
      case GENIE_NAK: {
          while ( deviceSerial->peek() == GENIE_NAK ) deviceSerial->read();
          if ( !genieStart && !NAK_detected && debugSerial != false ) APP_PRINT("[Genie]: Received NAK!\n");
          NAK_detected = 1;
          NAK_recovery_counter++;
          if ( NAK_recovery_counter >= 2 ) {
            NAK_recovery_counter = 0;
            deviceSerial->write(0xFF);
          }
          return GENIE_NAK;
        }
      default: {
          if ( displayDetected && !NAK_detected && debugSerial != false ) {
              APP_PRINT("[Genie]: Bad Byte: ");
              APP_PRINT("%d\n", deviceSerial->read());
          }
          break;
        }
    }
  }
  tick++;
  tick++;
  tick++;
  tick++;
  dequeue_processing();
  if ( !main_handler_active && _incomming_queue.size() && UserHandler != nullptr ) {
    main_handler_active = 1;
    UserHandler();
    main_handler_active = 0;
  }
  return -1;
}

// ######################################
// ## Dequeue Processing ################
// ######################################

void Genie::dequeue_processing() {
    tick+=10;
  if ( pendingACK ) { /* check if ACK timeout, clear flag */
    if ( millis() - pendingACK_timeout >= 500 ) {
      if ( debugSerial != false ) APP_PRINT("[Genie]: ACK timeout!\n");
      pendingACK = 0;
    }
  }
  else { /* if no ACK is expected, send another request from queue */
    if ( !block_dequeue && displayDetected && !NAK_detected && _outgoing_queue.size() ) {
      uint8_t _dequeued_buffer[7];
      _outgoing_queue.pop_front(_dequeued_buffer, 7);
      switch ( _dequeued_buffer[1] ) {
        case GENIE_WRITE_CONTRAST: {
            writeMode(&_dequeued_buffer[1], 3); /* allow writing to any form pages. */
            // if ( _dequeued_buffer[0] == currentForm ) writeMode(&_dequeued_buffer[1], 3); /* only allow writes to current form */
            break;
          }
        case GENIE_READ_OBJ: {
            writeMode(&_dequeued_buffer[1], 4);
            // if ( _dequeued_buffer[0] == currentForm ) writeMode(&_dequeued_buffer[1], 4);
            return;
          }
        case GENIE_WRITE_OBJ: {
            writeMode(&_dequeued_buffer[1], 6);
            // if ( _dequeued_buffer[0] == currentForm ) writeMode(&_dequeued_buffer[1], 6);
            break;
          }
      }
      pendingACK = 1;
      pendingACK_timeout = millis();
    }
  }
}

// ######################################
// ## Dequeue Event #####################
// ######################################
void Genie::DequeueEvent(genieFrame * buff) {
    tick+=2;
  if ( _incomming_queue.size() > 0) _incomming_queue.pop_front((uint8_t*)buff,6);
  event_frame = *buff;
}

// ######################################
// ## Write Strings #####################
// ######################################

bool Genie::WriteStr(uint8_t index, const char *string) {
  if ( !displayDetected ) {
    DoEvents();
    return 0;
  }
  uint8_t checksum = 0, buffer[4+strlen(string)];
  buffer[0] = GENIE_WRITE_STR;
  buffer[1] = index;
  buffer[2] = (uint8_t)strlen(string);
  memmove(&buffer[3],&string[0],strlen(string));
  for ( uint8_t i = 0; i < sizeof(buffer) - 1; i++ ) checksum ^= buffer[i];
  buffer[sizeof(buffer) - 1] = checksum;

  block_dequeue = 1; // disable dequeue
  while ( pendingACK ) DoEvents(); // wait pending ACKs
  writeMode(buffer,sizeof(buffer)); // write String
  pendingACK = 1; // enable ACK check
  pendingACK_timeout = millis(); // reset ACK check timer
  while ( pendingACK ) DoEvents(); // wait pending ACKs
  block_dequeue = 0; // re-enable dequeue

  tick = tick + 4 + sizeof(buffer);

  return 1;
}

uint16_t Genie::WriteStr(uint16_t index, long n) {
    tick++;
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    long N = n;
    n = abs(n);

    *str = '\0';

    do {
        unsigned long m = n;
        n /= 10;
        char c = m - 10 * n;
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);

    if (N < 0) *--str = '-';

    return WriteStr(index, str);
}

uint16_t Genie::WriteStr(uint16_t index, long n, int base) {
    tick++;
    tick++;
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    long N;
    *str = '\0';
    if(n>=0) {
        // prevent crash if called with base == 1
        if (base < 2) base = 10;
        if(base == 10) {
            N = n;
            n = abs(n);
        }

        do {
            unsigned long m = n;
            n /= base;
            char c = m - base * n;
            *--str = c < 10 ? c + '0' : c + 'A' - 10;
        } while(n);

        if(base == 10) {
            if (N < 0) *--str = '-';
        }

    }

    else if(n<0) {
        unsigned long n2 = (unsigned long)n;
        uint8_t base2 = base;
        do {
        unsigned long m = n2;
        n2 /= base2;
        char c = m - base2 * n2;
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
        } while(n2);

    }
    return WriteStr(index, str);
}

uint16_t Genie::WriteStr(uint16_t index, int n) {
    return WriteStr (index, (long) n);
}

uint16_t Genie::WriteStr(uint16_t index, int n, int base) {
    return WriteStr (index, (long) n, base);
}

uint16_t Genie::WriteStr(uint16_t index, unsigned long n) {
    tick++;
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    do {
        unsigned long m = n;
        n /= 10;
        char c = m - 10 * n;
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);

    return WriteStr(index, str);
}

uint16_t Genie::WriteStr(uint16_t index, unsigned long n, int base) {
    tick++;
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    // prevent crash if called with base == 1
    if (base < 2) base = 10;
    do {
        unsigned long m = n;
        n /= base;
        char c = m - base * n;
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);

    return WriteStr(index, str);
}

uint16_t Genie::WriteStr(uint16_t index, unsigned int n) {
    return WriteStr (index, (unsigned long) n);
}

uint16_t Genie::WriteStr(uint16_t index, unsigned n, int base) {
    return WriteStr (index, (unsigned long) n, base);
}


uint16_t Genie::WriteStr(uint16_t index, double number, int digits) {
    tick++;
    tick++;
    tick++;
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];
    *str = '\0';

    double number2 = number;
    if (number < 0.0) number = -number;

    // Round correctly so that print(1.999, 2) prints as "2.00"
    double rounding = 0.5;
    for (int i=0; i<digits; ++i)
    rounding /= 10.0;

    number += rounding;

    unsigned long int_part = (unsigned long)number;
    double remainder = number - (double)int_part;

    // Extract digits from the remainder one at a time
    int digits2 = digits;
    str = &buf[sizeof(buf) - 1 - digits2];
    while (digits2-- > 0)
    {
    remainder *= 10.0;
    int toPrint = int(remainder);
    char c = toPrint + 48;
    *str++ = c;
    remainder -= toPrint;
    }
    str = &buf[sizeof(buf) - 1 - digits];
    if (digits > 0) *--str = '.';

    // Extract the integer part of the number and print it
    do {
    unsigned long m = int_part;
    int_part /= 10;
    char c = m - 10 * int_part;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(int_part);

    // Handle negative numbers
    if (number2 < 0.0) *--str = '-';

    return WriteStr(index, str);
}

uint16_t Genie::WriteStr(uint16_t index, double n){
    return WriteStr(index, n, 2);
}

/////////////////////// WriteStrU ////////////////////////
//
// Write a string to the display (Unicode)
// Unicode characters are 2 bytes each
//
uint16_t Genie::WriteStrU (uint16_t index, uint16_t *string) {
    tick++;
    tick++;
  uint16_t *p;
  unsigned int checksum = 0;
  int len = 0;
  p = string;
  while (*p++) len++;
  if (len > 255) return -1;

  uint8_t buffer[4+(len*2)];
  buffer[0] = GENIE_WRITE_STRU;
  buffer[1] = (uint8_t)index;
  buffer[2] = (uint8_t)(len);
  for ( uint8_t i = 0; i < 3; i++ ) checksum ^= buffer[i];

  p = string;
  int run = 2;

  while (*p) {
    run++;
    buffer[run] = (*p >> 8);
    checksum ^= *p >> 8;
    run++;
    buffer[run] = (*p);
    checksum ^= *p++ & 0xff;
  }
  buffer[(4+(len*2))-1] = checksum;

  block_dequeue = 1; // disable dequeue
  while ( pendingACK ) DoEvents(); // wait pending ACKs
  writeMode(buffer,sizeof(buffer)); // write String
  pendingACK = 1; // enable ACK check
  pendingACK_timeout = millis(); // reset ACK check timer
  while ( pendingACK ) DoEvents(); // wait pending ACKs
  block_dequeue = 0; // re-enable dequeue

  return 1;
}

// ######################################
// ## Write WriteInhLabel Strings #######
// ######################################

bool Genie::WriteInhLabel(uint8_t index, const char *string) {
    tick++;
    tick++;
  if ( !displayDetected ) {
    DoEvents();
    return 0;
  }
  uint8_t checksum = 0, buffer[4+strlen(string)];
  buffer[0] = GENIE_WRITE_INH_LABEL;
  buffer[1] = index;
  buffer[2] = (uint8_t)strlen(string);
  memmove(&buffer[3],&string[0],strlen(string));
  for ( uint8_t i = 0; i < sizeof(buffer) - 1; i++ ) checksum ^= buffer[i];
  buffer[sizeof(buffer) - 1] = checksum;

  block_dequeue = 1; // disable dequeue
  while ( pendingACK ) DoEvents(); // wait pending ACKs
  writeMode(buffer,sizeof(buffer)); // write String
  pendingACK = 1; // enable ACK check
  pendingACK_timeout = millis(); // reset ACK check timer
  while ( pendingACK ) DoEvents(); // wait pending ACKs
  block_dequeue = 0; // re-enable dequeue

  return 1;
}

// ######################################
// ## Write WriteInhLabel Long ##########
// ######################################

uint16_t Genie::WriteInhLabel (uint16_t index) {
    return WriteObject(GENIE_OBJ_ILABELB, index, -1);
}

// ######################################
// ## Write WriteInhLabel Long ##########
// ######################################

uint16_t Genie::WriteInhLabel (uint16_t index, long n) {
    tick++;
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  long N = n;
  n = abs(n);

  *str = '\0';

  do {
    unsigned long m = n;
    n /= 10;
    char c = m - 10 * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  if (N < 0) *--str = '-';

  return WriteInhLabel(index, str);
}

// ######################################
// ## Write WriteInhLabel Long w/Base ###
// ######################################

uint16_t Genie::WriteInhLabel (uint16_t index, long n, int base) {
    tick++;
    tick++;
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  long N;
  *str = '\0';
  if(n>=0) {
    // prevent crash if called with base == 1
    if (base < 2) base = 10;
    if(base == 10) {
      N = n;
      n = abs(n);
    }
    do {
      unsigned long m = n;
      n /= base;
      char c = m - base * n;
      *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);

    if(base == 10) {
      if (N < 0) *--str = '-';
    }
  }

  else if(n<0) {
    unsigned long n2 = (unsigned long)n;
    uint8_t base2 = base;
    do {
    unsigned long m = n2;
    n2 /= base2;
    char c = m - base2 * n2;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n2);
  }
  return WriteInhLabel(index, str);
}

// ######################################
// ## Write WriteInhLabel Int ###########
// ######################################

uint16_t Genie::WriteInhLabel (uint16_t index, int n) {
  return WriteInhLabel (index, (long) n);
}

// ######################################
// ## Write WriteInhLabel Int w/Base ####
// ######################################

uint16_t Genie::WriteInhLabel (uint16_t index, int n, int base) {
  return WriteInhLabel (index, (long) n, base);
}

// ######################################
// ## Write WriteInhLabel UL ############
// ######################################

uint16_t Genie::WriteInhLabel (uint16_t index, unsigned long n) {
    tick++;
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  do {
    unsigned long m = n;
    n /= 10;
    char c = m - 10 * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return WriteInhLabel(index, str);
}

// ######################################
// ## Write WriteInhLabel UL w/Base #####
// ######################################

uint16_t Genie::WriteInhLabel (uint16_t index, unsigned long n, int base) {
    tick++;
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;
  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return WriteInhLabel(index, str);
}

uint16_t Genie::WriteInhLabel (uint16_t index, unsigned int n) {
  return WriteInhLabel (index, (unsigned long) n);
}

uint16_t Genie::WriteInhLabel (uint16_t index, unsigned n, int base) {
  return WriteInhLabel (index, (unsigned long) n, base);
}

// ######################################
// ## Write WriteInhLabel Floats #######
// ######################################

uint16_t Genie::WriteInhLabel (uint16_t index, double number, int digits) {
    tick++;
    tick++;
    tick++;
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];
  *str = '\0';

  double number2 = number;
  if (number < 0.0) number = -number;

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (int i = 0; i < digits; ++i) rounding /= 10.0;

  number += rounding;

  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;

  // Extract digits from the remainder one at a time
  int digits2 = digits;
  str = &buf[sizeof(buf) - 1 - digits2];
  while (digits2-- > 0) {
    remainder *= 10.0;
    int toPrint = int(remainder);
    char c = toPrint + 48;
    *str++ = c;
    remainder -= toPrint;
  }
  str = &buf[sizeof(buf) - 1 - digits];
  if (digits > 0) *--str = '.';

  // Extract the integer part of the number and print it
  do {
    unsigned long m = int_part;
    int_part /= 10;
    char c = m - 10 * int_part;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (int_part);

  // Handle negative numbers
  if (number2 < 0.0) *--str = '-';

  return WriteInhLabel(index, str);
}

uint8_t Genie::EventIs(genieFrame * e, uint8_t cmd, uint8_t object, uint8_t index) {
  return (e->reportObject.cmd == cmd && e->reportObject.object == object && e->reportObject.index == index);
}

uint16_t Genie::GetEventData(genieFrame * e) {
  return (e->reportObject.data_msb << 8) + e->reportObject.data_lsb;
}

// ######################################
// ## Write Magic Bytes #################
// ######################################

int8_t Genie::WriteMagicBytes(uint8_t index, uint8_t *bytes, uint8_t len, uint8_t report) {
    tick++;
    tick++;
    tick++;
  if ( !displayDetected ) {
    DoEvents();
    return -1;
  }
  uint8_t checksum = 0, buffer[4 + len];
  buffer[0] = GENIEM_WRITE_BYTES;
  buffer[1] = index;
  buffer[2] = len;
  memmove(&buffer[3], bytes, len);
  for ( uint8_t i = 0; i < sizeof(buffer) - 1; i++ ) checksum ^= buffer[i];
  buffer[sizeof(buffer) - 1] = checksum;

  block_dequeue = 1;
  while ( pendingACK ) DoEvents();
  writeMode(buffer, sizeof(buffer));

  if ( report ) {
    while ( pendingACK ) DoEvents();
    block_dequeue = 0;
    return 1;
  }

  uint32_t timeout = millis();
  while (millis() - timeout < 1000) {
    uint8_t result = DoEvents();
    switch ( result ) {
      case GENIEM_REPORT_BYTES: {
          block_dequeue = 0;
          return result;
        }
      case GENIE_ACK: {
          block_dequeue = 0;
          return result;
        }
      case GENIE_NAK: {
          block_dequeue = 0;
          return result;
        }
    }
  }
  block_dequeue = 0;
  return -1;
}

// ######################################
// ## Write Magic Double Bytes ##########
// ######################################

int8_t Genie::WriteMagicDBytes(uint8_t index, uint16_t *shorts, uint8_t len, uint8_t report) {
    tick++;
    tick++;
    tick++;
  if ( !displayDetected ) {
    DoEvents();
    return -1;
  }
  uint8_t checksum = 0, buffer[4+len*2];
  buffer[0] = GENIEM_WRITE_DBYTES;
  buffer[1] = index;
  buffer[2] = len;
  bool odd_or_even = ( len % 2 );
  for ( uint16_t i = 0, j = 0; i < len; i++ ) {
    buffer[j+3] = shorts[i] >> 8;
    buffer[j+4] = (uint8_t)shorts[i];
    j+=2;
  }
  if ( odd_or_even ) buffer[sizeof(buffer)-1] = shorts[len-2];
  for ( uint8_t i = 0; i < sizeof(buffer) - 1; i++ ) checksum ^= buffer[i];
  buffer[sizeof(buffer) - 1] = checksum;

  block_dequeue = 1;
  while ( pendingACK ) DoEvents();
  writeMode(buffer, sizeof(buffer));

  if ( report ) {
    block_dequeue = 0;
    while ( pendingACK ) DoEvents();
    return 1;
  }

  uint32_t timeout = millis();
  while (millis() - timeout < 1000) {
    uint8_t result = DoEvents();
    switch ( result ) {
      case GENIEM_REPORT_BYTES: {
          block_dequeue = 0;
          return result;
        }
      case GENIE_ACK: {
          block_dequeue = 0;
          return result;
        }
      case GENIE_NAK: {
          block_dequeue = 0;
          return result;
        }
    }
  }
  block_dequeue = 0;
  return -1;
}

// ######################################
// ## GenieObject Class #################
// ######################################

GenieObject::GenieObject(Genie& _instance, uint8_t obj, uint8_t idx) {
  object = obj;
  index = idx;
  instance = &_instance;
}

// ######################################
// ## GenieObject read ##################
// ######################################

int32_t GenieObject::read(bool state) {
  return instance->ReadObject(object, index, state);
}

// ######################################
// ## GenieObject write #################
// ######################################

void GenieObject::write(uint16_t data) {
  instance->WriteObject(object, index, data);
}

void GenieObject::write(const char * data) {
    tick++;
  if ( object == GENIE_WRITE_STR ) instance->WriteStr(index, data);
  else if ( object == GENIE_WRITE_INH_LABEL ) instance->WriteInhLabel(index, data);
}

#endif
