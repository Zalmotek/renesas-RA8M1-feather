/*!
 * @file  DFRobot_DF2301Q.h
 * @brief  Basic structure of DFRobot_DF2301Q class
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-12-30
 * @url  https://github.com/DFRobot/DFRobot_DF2301Q
*/
#ifndef DFRobot_DF2301Q_H
#define DFRobot_DF2301Q_H

#include <Wire.h>
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
#include <SoftwareSerial.h>
#endif

// #define ENABLE_DBG   //!< Open this macro and you can see the details of the program
#ifdef ENABLE_DBG
  #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
  #define DBG(...)
#endif

#define DF2301Q_I2C_ADDR                 uint8_t(0x64)   //!< I2C address

#define DF2301Q_I2C_REG_CMDID            uint8_t(0x02)   //!< Address of the register for requesting command word ID
#define DF2301Q_I2C_REG_PLAY_CMDID       uint8_t(0x03)   //!< Address of the register for playing audio by command word ID
#define DF2301Q_I2C_REG_SET_MUTE         uint8_t(0x04)   //!< Register for setting mute mode
#define DF2301Q_I2C_REG_SET_VOLUME       uint8_t(0x05)   //!< Register for setting volume
#define DF2301Q_I2C_REG_WAKE_TIME        uint8_t(0x06)   //!< Address of the register for wake-up time

#define DF2301Q_UART_BAUDRATE            long(9600)      //!< UART baud rate
#define DF2301Q_UART_MSG_DATA_MAX_SIZE   uint8_t(8)      //!< Maximum data length of serial data frame

/*header*/
#define DF2301Q_UART_MSG_HEAD_LOW    uint8_t(0xF4)
#define DF2301Q_UART_MSG_HEAD_HIGH   uint8_t(0xF5)
#define DF2301Q_UART_MSG_HEAD        ((DF2301Q_UART_MSG_HEAD_HIGH<<8)|DF2301Q_UART_MSG_HEAD_LOW)
/*tail*/
#define DF2301Q_UART_MSG_TAIL        uint8_t(0xFB)
/*msgType*/
#define DF2301Q_UART_MSG_TYPE_CMD_UP          uint8_t(0xA0)
#define DF2301Q_UART_MSG_TYPE_CMD_DOWN        uint8_t(0xA1)
#define DF2301Q_UART_MSG_TYPE_ACK             uint8_t(0xA2)
#define DF2301Q_UART_MSG_TYPE_NOTIFY          uint8_t(0xA3)
/*msgCmd*/
#define DF2301Q_UART_MSG_CMD_ASR_RESULT       uint8_t(0x91)           //Report voice recognition results
#define DF2301Q_UART_MSG_CMD_PLAY_VOICE       uint8_t(0x92)           //Play local broadcast audio
#define DF2301Q_UART_MSG_CMD_GET_FLASHUID     uint8_t(0x93)           //Read the serial number of FLASH
#define DF2301Q_UART_MSG_CMD_GET_VERSION      uint8_t(0x94)           //Read version number
#define DF2301Q_UART_MSG_CMD_RESET_MODULE     uint8_t(0x95)           //Reset the voice module
#define DF2301Q_UART_MSG_CMD_SET_CONFIG       uint8_t(0x96)           //Settings
#define DF2301Q_UART_MSG_CMD_ENTER_OTA_MODE   uint8_t(0x97)          //Enter update mode
#define DF2301Q_UART_MSG_CMD_NOTIFY_STATUS    uint8_t(0x9A)           //Event notification
#define DF2301Q_UART_MSG_CMD_ACK_COMMON       uint8_t(0xAA)
/* !!! if user want add please add form DF2301Q_UART_MSG_CMD_USER_START*/
#define DF2301Q_UART_MSG_CMD_USER_START       uint8_t(0xB0)
/*msgData  msgCmd:DF2301Q_UART_MSG_CMD_PLAY_VOICE*/
#define DF2301Q_UART_MSG_DATA_PLAY_START      uint8_t(0x80)
#define DF2301Q_UART_MSG_DATA_PLAY_PAUSE      uint8_t(0x81)
#define DF2301Q_UART_MSG_DATA_PLAY_RESUME     uint8_t(0x82)
#define DF2301Q_UART_MSG_DATA_PLAY_STOP       uint8_t(0x83)
#define DF2301Q_UART_MSG_DATA_PLAY_BY_VOICEID       uint8_t(0x90)
#define DF2301Q_UART_MSG_DATA_PLAY_BY_SEMANTIC_ID   uint8_t(0x91)
#define DF2301Q_UART_MSG_DATA_PLAY_BY_CMD_ID        uint8_t(0x92)
/*msgData  msg_cmd:DF2301Q_UART_MSG_CMD_GET_VERSION*/
#define DF2301Q_UART_MSG_DATA_VER_PROTOCOL    uint8_t(0x80)         // Serial protocol version number
#define DF2301Q_UART_MSG_DATA_VER_SDK         uint8_t(0x81)         // SDK version number
#define DF2301Q_UART_MSG_DATA_VER_ASR         uint8_t(0x82)         // ASR component version number
#define DF2301Q_UART_MSG_DATA_VER_PREPROCESS  uint8_t(0x83)         // Audio pre-processing algorithm version number
#define DF2301Q_UART_MSG_DATA_VER_PLAYER      uint8_t(0x84)         // Player version number
#define DF2301Q_UART_MSG_DATA_VER_APP         uint8_t(0x8A)         // App version number
/*msgData  msg_cmd:DF2301Q_UART_MSG_CMD_NOTIFY_STATUS*/
#define DF2301Q_UART_MSG_DATA_NOTIFY_POWERON       uint8_t(0xB0)
#define DF2301Q_UART_MSG_DATA_NOTIFY_WAKEUPENTER   uint8_t(0xB1)
#define DF2301Q_UART_MSG_DATA_NOTIFY_WAKEUPEXIT    uint8_t(0xB2)
#define DF2301Q_UART_MSG_DATA_NOTIFY_PLAYSTART     uint8_t(0xB3)
#define DF2301Q_UART_MSG_DATA_NOTIFY_PLAYEND       uint8_t(0xB4)
/*msgData msg_cmd:DF2301Q_UART_MSG_CMD_SET_CONFIG*/
#define DF2301Q_UART_MSG_CMD_SET_VOLUME        uint8_t(0x80)
#define DF2301Q_UART_MSG_CMD_SET_ENTERWAKEUP   uint8_t(0x81)
#define DF2301Q_UART_MSG_CMD_SET_PRT_MID_RST   uint8_t(0x82)
#define DF2301Q_UART_MSG_CMD_SET_MUTE          uint8_t(0x83)
#define DF2301Q_UART_MSG_CMD_SET_WAKE_TIME     uint8_t(0x84)
#define DF2301Q_UART_MSG_CMD_SET_NEEDACK       uint8_t(0x90)
#define DF2301Q_UART_MSG_CMD_SET_NEEDSTRING    uint8_t(0x91)
/*ACK error code*/
#define DF2301Q_UART_MSG_ACK_ERR_NONE          uint8_t(0x0)
#define DF2301Q_UART_MSG_ACK_ERR_CHECKSUM      uint8_t(0xff)
#define DF2301Q_UART_MSG_ACK_ERR_NOSUPPORT     uint8_t(0xfe)

class DFRobot_DF2301Q
{
public:
  /**
   * @fn DFRobot_DF2301Q
   * @brief Constructor
   * @return None
   */
  DFRobot_DF2301Q();

  /**
   * @fn begin
   * @brief Init function
   * @return bool type, true if successful, false if error
   */
  virtual bool begin(void) = 0;

private:

};

/**************************************************************************
                          Subclass using I2C interface for communication
 **************************************************************************/

class DFRobot_DF2301Q_I2C: public DFRobot_DF2301Q
{
public:
  /**
   * @fn DFRobot_DF2301Q_I2C
   * @brief Constructor
   * @param pWire I2C bus pointer object, construct the device. You can pass a parameter to it or not, default to be Wire
   * @param address 7bits I2C address, the first three bits determine the value of the address, default to 0x50
   * @return None
   */
  DFRobot_DF2301Q_I2C(uint8_t i2cAddr=DF2301Q_I2C_ADDR);

  /**
   * @fn begin
   * @brief Subclass init function
   * @return Bool type, true for success, false for failure
   */
  virtual bool begin(void);

  /**
   * @fn getCMDID
   * @brief Get the ID corresponding to the command word
   * @return Return the obtained command word ID, returning 0 means no valid ID is obtained
   */
  uint8_t getCMDID(void);

  /**
   * @fn playByCMDID
   * @brief Play the corresponding reply audio according to the command word ID
   * @param CMDID - Command word ID
   * @return None
   * @note Can enter wake-up state through ID-1 in I2C mode
   */
  void playByCMDID(uint8_t CMDID);

  /**
   * @fn getWakeTime
   * @brief Get the wake-up duration
   * @return The current set wake-up period
   */
  uint8_t getWakeTime(void);

  /**
   * @fn setWakeTime
   * @brief Set wake-up duration
   * @param wakeTime - Wake-up duration(0-255)
   * @return None
   */
  void setWakeTime(uint8_t wakeTime);

  /**
   * @fn setVolume
   * @brief Set volume
   * @param vol - Volume range(1-7)
   * @return None
   */
  void setVolume(uint8_t vol);

  /**
   * @fn setMuteMode
   * @brief Set mute mode
   * @param mode - Mute mode; set value 1: mute, 0: unmute
   * @return None
   */
  void setMuteMode(uint8_t mode);

protected:
  /**
   * @fn writeReg
   * @brief Write register value through I2C bus
   * @param reg  Register address 8bits
   * @param pBuf Storage and buffer for data to be written
   * @return None
   */
  void writeReg(uint8_t reg, const void* pBuf);

  /**
   * @fn readReg
   * @brief Read register value through I2C bus
   * @param reg  Register address 8bits
   * @param pBuf Storage and buffer for data to be read
   * @return Return the read length, returning 0 means reading failed
   */
  size_t readReg(uint8_t reg, void* pBuf);

private:
  uint8_t _deviceAddr;   // Address of the device for I2C communication
};

/**************************************************************************
                          Subclass using UART interface for communication
 **************************************************************************/

class DFRobot_DF2301Q_UART: public DFRobot_DF2301Q
{
public:
  #pragma pack(1)
  /**
   * @struct sUartMsg_t
   * @brief Serial data frame   struct
   */
  typedef struct
  {
    uint16_t header;
    uint16_t dataLength;
    uint8_t msgType;
    uint8_t msgCmd;
    uint8_t msgSeq;
    uint8_t msgData[DF2301Q_UART_MSG_DATA_MAX_SIZE];
    // uint16_t chkSum;   /* send add auto */
    // uint8_t tail;   /* send add auto */
  }sUartMsg_t;

  /**
   * @enum eReceiveState_t
   * @brief receive use state machine method, so two char can arrive different time
   */
  typedef enum
  {
    REV_STATE_HEAD0   = 0x00,
    REV_STATE_HEAD1   = 0x01,
    REV_STATE_LENGTH0 = 0x02,
    REV_STATE_LENGTH1 = 0x03,
    REV_STATE_TYPE    = 0x04,
    REV_STATE_CMD     = 0x05,
    REV_STATE_SEQ     = 0x06,
    REV_STATE_DATA    = 0x07,
    REV_STATE_CKSUM0  = 0x08,
    REV_STATE_CKSUM1  = 0x09,
    REV_STATE_TAIL    = 0x0a,
  }eRecvState_t;

public:
  /**
   * @fn DFRobot_DF2301Q_UART
   * @brief  Constructor
   * @param serial - Serial communication, support hardware and software serial
   * @param rx - UART The pin for receiving data
   * @param tx - UART The pin for transmitting data
   * @return None
   */
  //DFRobot_DF2301Q_UART(HardwareSerial *hardSerial);
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
  DFRobot_DF2301Q_UART(SoftwareSerial *softSerial);
#elif defined(ESP32)
  DFRobot_DF2301Q_UART(HardwareSerial *hardSerial, uint8_t rx, uint8_t tx);
#endif

  /**
   * @fn begin
   * @brief Subclass init function
   * @return Bool type, true for success, false for failure
   */
  virtual bool begin();

  /**
   * @fn getCMDID
   * @brief Get the ID corresponding to the command word
   * @return Return the obtained command word ID, returning 0 means no valid ID is obtained
   */
  uint8_t getCMDID(void);

  /**
   * @fn playByCMDID
   * @brief Play the corresponding reply audio according to the command word ID
   * @param play_id - Command word ID
   * @return None
   */
  void playByCMDID(uint32_t play_id);

  /**
   * @fn resetModule
   * @brief Reset module
   * @return None
   */
  void resetModule(void);

  /**
   * @fn settingCMD
   * @brief Set commands of the module
   * @param setType - Set type
   * @n       DF2301Q_UART_MSG_CMD_SET_VOLUME : Set volume, the set value range 1-7
   * @n       DF2301Q_UART_MSG_CMD_SET_ENTERWAKEUP : Enter wake-up state; set value 0
   * @n       DF2301Q_UART_MSG_CMD_SET_MUTE : Mute mode; set value 1: mute, 0: unmute
   * @n       DF2301Q_UART_MSG_CMD_SET_WAKE_TIME : Wake-up duration; the set value range 0-255s
   * @param setValue - Set value, refer to the set type above for the range
   * @return None
   */
  void settingCMD(uint8_t setType, uint32_t setValue);

protected:
  /**
   * @fn sendPacket
   * @brief Write data via UART
   * @param msg - Data packet to be sent
   * @return None
   */
  void sendPacket(const sUartMsg_t * msg);

  /**
   * @fn recvPacket
   * @brief Read data via UART
   * @param msg - Buffer for receiving data packet
   * @return Return the read length, returning 0 means the reading failed
   */
  uint8_t recvPacket(sUartMsg_t * msg);

private:
  uint8_t _sendSequence, _uartCmdId;
};


DFRobot_DF2301Q::DFRobot_DF2301Q()
{
}

/**************************************************************************
                          Subclass using I2C interface for communication
 **************************************************************************/

DFRobot_DF2301Q_I2C::DFRobot_DF2301Q_I2C(uint8_t i2cAddr)
{
  _deviceAddr = i2cAddr;
}

bool DFRobot_DF2301Q_I2C::begin()
{
//  begin();   // Wire.h(I2C)library function initialize wire library
  beginTransmission(_deviceAddr);
  write(0x00);
  endTransmission(false);
  return true;
}

uint8_t DFRobot_DF2301Q_I2C::getCMDID(void)
{
  uint8_t CMDID = 0;
  readReg(DF2301Q_I2C_REG_CMDID, &CMDID);
  delay(50);   // Prevent the access rate from interfering with other functions of the voice module
  return CMDID;
}

void DFRobot_DF2301Q_I2C::playByCMDID(uint8_t CMDID)
{
  writeReg(DF2301Q_I2C_REG_PLAY_CMDID, &CMDID);
  delay(1000);
}

uint8_t DFRobot_DF2301Q_I2C::getWakeTime(void)
{
  uint8_t wakeTime = 0;
  readReg(DF2301Q_I2C_REG_WAKE_TIME, &wakeTime);
  return wakeTime;
}

void DFRobot_DF2301Q_I2C::setWakeTime(uint8_t wakeTime)
{
  writeReg(DF2301Q_I2C_REG_WAKE_TIME, &wakeTime);
}

void DFRobot_DF2301Q_I2C::setVolume(uint8_t vol)
{
  // if (vol < 0)
  //   vol = 0;
  // else if (vol > 20)
  //   vol = 20;
  writeReg(DF2301Q_I2C_REG_SET_VOLUME, &vol);
}

void DFRobot_DF2301Q_I2C::setMuteMode(uint8_t mode)
{
  if (0 != mode)
    mode = 1;
  writeReg(DF2301Q_I2C_REG_SET_MUTE, &mode);
}

void DFRobot_DF2301Q_I2C::writeReg(uint8_t reg, const void* pBuf)
{
  if(pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;

  beginTransmission(_deviceAddr);
  write(reg);
  write(*_pBuf);
  endTransmission(false);
}

size_t DFRobot_DF2301Q_I2C::readReg(uint8_t reg, void* pBuf)
{
  if(NULL == pBuf) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t*)pBuf;

  size_t count = 0;

  beginTransmission(_deviceAddr);
  write(reg);
  endTransmission(true);    // Used Wire.endTransmission() to end a slave transmission started by beginTransmission() and arranged by write().
    DBG("endTransmission ERROR!!");
  requestFrom(_deviceAddr, (uint8_t)1);   // Master device requests size bytes from slave device, which can be accepted by master device with read() or available()

    while (available()) {
      _pBuf[count++] = read();   // Use read() to receive and put into buf
      // DBG(_pBuf[count-1], HEX);
    }
    // _pWire->endTransmission();

  return count;
}

/**************************************************************************
                          Subclass using UART interface for communication
 **************************************************************************/

//DFRobot_DF2301Q_UART::DFRobot_DF2301Q_UART(HardwareSerial *hardSerial)
//{
//
//#if !(defined(ARDUINO_SAM_ZERO))   // Initializing the M0 board now will lead to maincontroller program crash
//  hardSerial->begin(DF2301Q_UART_BAUDRATE);
//#endif
//  _ser = hardSerial;
//}

#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
DFRobot_DF2301Q_UART::DFRobot_DF2301Q_UART(SoftwareSerial *softSerial)
{
  softSerial->begin(DF2301Q_UART_BAUDRATE);
  _ser = softSerial;
}
#elif defined(ESP32)
DFRobot_DF2301Q_UART::DFRobot_DF2301Q_UART(HardwareSerial *hardSerial, uint8_t rx, uint8_t tx)
{
  hardSerial->begin(DF2301Q_UART_BAUDRATE, SERIAL_8N1, rx, tx);
  _ser = hardSerial;
}
#endif

bool DFRobot_DF2301Q_UART::begin()
{
#if defined(ARDUINO_SAM_ZERO)   // The M0 board needs to be initialized at this time
  ((HardwareSerial *)_ser)->begin(DF2301Q_UART_BAUDRATE);
#endif

  _sendSequence = 0;

  if(NULL){
    return false;
  }
  return true;
}

uint8_t DFRobot_DF2301Q_UART::getCMDID(void)
{
  sUartMsg_t msg;
  _uartCmdId = 0;
  recvPacket(&msg);
  return _uartCmdId;
}

void DFRobot_DF2301Q_UART::playByCMDID(uint32_t play_id)
{
    sUartMsg_t msg;

    msg.header = DF2301Q_UART_MSG_HEAD;
    msg.dataLength = 6;
    msg.msgType = DF2301Q_UART_MSG_TYPE_CMD_DOWN;
    msg.msgCmd = DF2301Q_UART_MSG_CMD_PLAY_VOICE;
    msg.msgSeq = _sendSequence++;
    msg.msgData[0] = DF2301Q_UART_MSG_DATA_PLAY_START;
    msg.msgData[1] = DF2301Q_UART_MSG_DATA_PLAY_BY_CMD_ID;
    memcpy(&msg.msgData[2], &play_id, sizeof(uint32_t));

    sendPacket(&msg);
    delay(1000);
}

void DFRobot_DF2301Q_UART::resetModule(void)
{
    sUartMsg_t msg;

    msg.header = DF2301Q_UART_MSG_HEAD;
    msg.dataLength = 5;
    msg.msgType = DF2301Q_UART_MSG_TYPE_CMD_DOWN;
    msg.msgCmd = DF2301Q_UART_MSG_CMD_RESET_MODULE;
    msg.msgSeq = _sendSequence++;
    msg.msgData[0] = 'r';
    msg.msgData[1] = 'e';
    msg.msgData[2] = 's';
    msg.msgData[3] = 'e';
    msg.msgData[4] = 't';

    sendPacket(&msg);
    delay(3000);
}

void DFRobot_DF2301Q_UART::settingCMD(uint8_t setType, uint32_t setValue)
{
    sUartMsg_t msg;

    msg.header = DF2301Q_UART_MSG_HEAD;
    msg.dataLength = 5;
    msg.msgType = DF2301Q_UART_MSG_TYPE_CMD_DOWN;
    msg.msgCmd = DF2301Q_UART_MSG_CMD_SET_CONFIG;
    msg.msgSeq = _sendSequence++;
    msg.msgData[0] = setType;
    memcpy(&msg.msgData[1], &setValue, sizeof(setValue));

    sendPacket(&msg);
}

void DFRobot_DF2301Q_UART::sendPacket(const sUartMsg_t * msg)
{
  if(NULL == msg) {
    DBG("msg ERROR!! : null pointer");
  }
  uint8_t *_pBuf = (uint8_t *)msg;

  while (available()) {
    read();
  }

  uint16_t i = 0;
  /*header and data*/
  for(; i<4; i++) {
    write( _pBuf[i] );
  }

  uint16_t chkSum = 0;
  for(; i<(msg->dataLength + 7); i++) {
    chkSum += _pBuf[i];
    write( _pBuf[i] );
  }

  /*check sum*/
  write( chkSum & 0xff );
  write( (chkSum >> 8) & 0xff );

  /*tail*/
  write( DF2301Q_UART_MSG_TAIL );

  delay(100);
}

uint8_t DFRobot_DF2301Q_UART::recvPacket(sUartMsg_t * msg)
{
  if(NULL == msg) {
    DBG("msg ERROR!! : null pointer");
  }

  uint8_t revState = REV_STATE_HEAD0, receiveChar;
  uint16_t length0 = 0, length1 = 0;
  uint16_t chkSum0 = 0, chkSum1 = 0;
  uint16_t dataRevCount = 0;

  while(available()) {
    receiveChar = read();
    switch(revState) {
      case REV_STATE_HEAD0:
        if(DF2301Q_UART_MSG_HEAD_LOW == receiveChar) {
          revState = REV_STATE_HEAD1;
        }
        break;
      case REV_STATE_HEAD1:
        if(DF2301Q_UART_MSG_HEAD_HIGH == receiveChar) {
          revState = REV_STATE_LENGTH0;
          msg->header = DF2301Q_UART_MSG_HEAD;
        } else {
          if(DF2301Q_UART_MSG_HEAD_LOW != receiveChar) {
            revState = REV_STATE_HEAD0;
          }
        }
        break;
      case REV_STATE_LENGTH0:
        length0 = receiveChar;
        revState = REV_STATE_LENGTH1;
        break;
      case REV_STATE_LENGTH1:
        length1 = receiveChar;
        length1 <<= 8;
        length1 += length0;
        if(length1 <= DF2301Q_UART_MSG_DATA_MAX_SIZE) {
            msg->dataLength = length1;
            revState = REV_STATE_TYPE;
        } else {
            revState = REV_STATE_HEAD0;
        }
        break;
      case REV_STATE_TYPE:
        msg->msgType = receiveChar;
        revState = REV_STATE_CMD;
        break;
      case REV_STATE_CMD:
        msg->msgCmd = receiveChar;
        revState = REV_STATE_SEQ;
        break;
      case REV_STATE_SEQ:
        msg->msgSeq = receiveChar;
        if(length1 > 0) {
            revState = REV_STATE_DATA;
            dataRevCount = 0;
        } else {
            revState = REV_STATE_CKSUM0;
        }
        break;
      case REV_STATE_DATA:
        msg->msgData[dataRevCount] = receiveChar;
        dataRevCount += 1;
        if(dataRevCount == length1) {
            revState = REV_STATE_CKSUM0;
        }
        break;
      case REV_STATE_CKSUM0:
        chkSum0 = receiveChar;
        revState = REV_STATE_CKSUM1;
        break;
      case REV_STATE_CKSUM1:
      {
        uint16_t packetChkSum = 0;
        uint8_t *data = (uint8_t *)msg;
        for(uint16_t i=4; i<(msg->dataLength + 7); i++) {
          packetChkSum += data[i];
        }

        chkSum1 = receiveChar;
        chkSum1 <<= 8;
        chkSum1 += chkSum0;

        /*msg->chksum = chkSum1; just used as judgement*/
        if(chkSum1 == packetChkSum) {
          revState = REV_STATE_TAIL;
        } else {
          revState = REV_STATE_HEAD0;
        }
        break;
      }
      case REV_STATE_TAIL:
        if(receiveChar == DF2301Q_UART_MSG_TAIL) {   /*receive ok*/
          /*msg->tail = receiveChar; just used as judgement*/
          if(DF2301Q_UART_MSG_TYPE_CMD_UP == msg->msgType) {
            _uartCmdId = msg->msgData[0];
            DBG(_uartCmdId, HEX);
          }

        } else {
          dataRevCount = 0;
        }
        revState = REV_STATE_HEAD0;
        break;
      default:
        revState = REV_STATE_HEAD0;
        break;
    }
  }

  return dataRevCount;
}

#endif
