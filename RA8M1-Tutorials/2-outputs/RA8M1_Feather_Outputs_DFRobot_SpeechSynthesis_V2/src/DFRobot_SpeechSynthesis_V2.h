#ifndef DFROBOT_SPEECHSYNTHESIS_V2_H
#define DFROBOT_SPEECHSYNTHESIS_V2_H

#include <Wire.h>
#include <string>

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define I2C_ADDR               0x40  //i2c address
#define INQUIRYSTATUS          0x21  //Check status
#define ENTERSAVEELETRI        0x88
#define WAKEUP                 0xFF  //Wake-up command

#define START_SYNTHESIS        0x01  //Start synthesis command 0
#define START_SYNTHESIS1       0x02  //Start synthesis command 1
#define STOP_SYNTHESIS         0x02  //End speech synthesis
#define PAUSE_SYNTHESIS        0x03  //pause speech synthesis command
#define RECOVER_SYNTHESIS      0x04  //Resume speech synthesis commands

#define pgm_read_byte(addr) (*(addr))  // Direct access for non-AVR environments

class DFRobot_SpeechSynthesis {
public:
  #define ERR_OK             0      //No error
  #define ERR_DATA_BUS      -1      //Data bus error
  #define ERR_IC_VERSION    -2      //Chip version does not match


  typedef struct
  {
    uint8_t ischar ;
    uint16_t index;
    uint16_t length;

  }sSubMess_t;

  /**！
   *@enum eSpeechStyle_t Speech Synthesis style
   */
  typedef enum{
    eCaton,/**<Word by word>*/
    eSmooth,/**<Fluently>*/
  } eSpeechStyle_t;

  /**
   *@enum ePinyin_t Whether synthesize PinYin
   */
  typedef enum{
    ePinyinEnable,/**<Synthesize PinYin>*/
    ePinyinDisable,/**<Not>*/
  } ePinyin_t;

  /**
   *@enum eLanguage_t Synthesize Arabic number, unit, special character into Chinese or English
   */
  typedef enum{
    eChinesel,/**<Chinese>*/
    eEnglishl,/**<English>*/
    eAutoJudgel,/**<Auto Judge>*/
  } eLanguage_t;

  /**
   *@enum eDigitalPron_t How to  read long numbers
   */
  typedef enum{
    eNumber,/**<Telephone number>*/
    eNumeric,/**<Number>*/
    eAutoJudged,/**<Auto Judge>*/
  } eDigitalPron_t;

  /**
   *@enum eZeroPron_t How to read "0"
   */
  typedef enum{
    eZreo,/**<Read as 'zero'>*/
    eOu,/**<Read as'ou'>*/
  } eZeroPron_t;

  /**
   *@enum eOnePron_t How to read "1"
   */
  typedef enum{
    eYao,/**<Read as 'yao'>*/
    eChone,/**<Read as 'yi'>*/
  } eOnePron_t;

  /**
   *@enum eNamePron_t The function is only used for Chinese reading
   */
  typedef enum{
    eName,
    eAutoJudgedn,
  } eNamePron_t;

  /**
   *@enum eSoundType_t Select sound type
   */
  typedef enum{
    eFemale1,    /**<Female 1, recommended>*/
    eMale1,      /**<Male 1, recommended>*/
    eMale2,      /**<Male 2>*/
    eFemale2,    /**<FEMALE 2>*/
    eDonaldDuck, /**<Donald Duck>*/
    eFemale3,    /**<Female 3>*/
  } eSoundType_t;

  /**
   *@enum eENpron_t How to read English
   */
  typedef enum{
   eAlphabet,/**<Spell>*/
   eWord,/**<word>*/
  } eENpron_t;

  typedef enum{
    eChinese,
    eEnglish,
    eNone,
  } eState_t;

public:

  /**
   * @fn DFRobot_SpeechSynthesis
   * @brief Constructor
   * @param pWire I2C BUS pointer object， construct device, can pass parameter or not, default to Wire
   * @param address 7bits I2C address, the first three bits determine the value of the address, default to 0x50
   */
  DFRobot_SpeechSynthesis();

  /**
   * @fn speak
   * @brief Speech synthesis function
   * @param word Content to be synthesized, could be Chinese, English, Number, etc.
   */
  void speak(std::string word);

  /**
   * @fn speak
   * @brief Speech synthesis function
   * @param word Content to be synthesized, could be Chinese, English, Number, etc.
   */
  void speak(const void *data);

  /**
   * @fn speak
   * @brief Speech synthesis function,the data to be converted is put into Flash
   * @param word Content to be synthesized, could be Chinese, English, Number, etc.
   */
  void speak(const char *data);

  /**
   * @fn sleep
   * @brief Set sensor to sleep mode
   */
  void sleep();

  /**
   * @fn wakeup
   * @brief Wake up sensor from sleep mode
   */
  void wakeup();

  /**
   * @fn setVolume
   * @brief Set voice volume
   * @param voc  Volume value(0-9)
   */
  void setVolume(uint8_t voc);

  /**
   * @fn setSpeed
   * @brief Set playback speed
   * @param speed Speed value (0-9)
   */
  void setSpeed(uint8_t speed);

  /**
   * @fn setSoundType
   * @brief Set sound type
   * @param type eMale:Male, eFemale:Female, eDonaldduck: Donaldduck
   */
  void setSoundType(eSoundType_t type);

  /**
   * @fn setTone
   * @brief Set the tone
   * @param tone Tone value (0-9)
   */
  void setTone(uint8_t tone);

  /**
   * @fn setEnglishPron
   * @brief Set how to read English
   * @param pron eAlphabet: letter, eWord: word
   */
  void setEnglishPron(eENpron_t pron);

  /**
   * @fn reset
   * @brief Reset settings to default
   */
  void reset();

  /**
   * @fn enableRhythm
   * @brief  The function is only used for Chinese reading
   * @param enable true,false
   */
  void enableRhythm(bool enable);

  /**
   * @fn setOnePron
   * @brief Set how to read "1" in phone number
   * @param pron eYao: read as "yao", eChone: read as "yi"
   */
  void setOnePron(eOnePron_t pron);

  /**
   * @fn setNamePron
   * @brief Set whether to use surname reading principle mandatorily
   * @param pron eName: force, eAutojudgedn: auto judge
   */
  void setNamePron(eNamePron_t pron);

  /**
   * @fn setZeroPron
   * @brief set how to read "0" in phone number
   * @details set the sound of zero
   * @param pron eZreo: read as "zero", eOu: read as "ou"
   */
  void setZeroPron(eZeroPron_t pron);

  /**
   * @fn setLanguage
   * @brief  Synthesize Arabic number, unit, special character into Chinese or English
   * @param style eChinesel: Chinese, eEnglishl: English, eAutojudgel: Auto judge
   */
  void setLanguage(eLanguage_t style);

  /**
   * @fn enablePINYIN
   * @brief Enable PinYin Synthesis
   * @details enable pinyin pronunciation
   * @param enable true: enable, false: disable
   */
  void enablePINYIN(bool enable);

  /**
   * @fn setSpeechStyle
   * @brief Set synthesis style
   * @param style eCaton: word by word, eSmooth: fluently
   */
  void setSpeechStyle(eSpeechStyle_t style);

  /**
   * @fn setDigitalPron
   * @brief Set how to read long numbers
   * @param pron eNumber: phone number, eNumeric: number, eAutojudged: Auto judge
   */
  void setDigitalPron(eDigitalPron_t pron);

  /**
   * @fn stopSynthesis
   * @brief Stop synthesis
   */
  void stopSynthesis();

  /**
   * @fn pauseSynthesis
   * @brief Synthesis pause
   */
  void pauseSynthesis();

  /**
   * @fn recoverSynthesis
   * @brief Recover synthesis
   * @details resumes from paused compositing state
   */
  void recoverSynthesis();

  /**
   * @fn wait
   * @brief Wait for speech synthesis to complete
   */
  void wait();

  /**
   * @fn speakElish
   * @brief Synthesize English char string
   * @param word english string
   */
  void speakElish(std::string word);

private:


  uint8_t *_utf8;
  uint8_t *_unicode;
  uint16_t uniLen = 0;
  uint16_t _index=0;
  uint16_t _len=0;
  uint16_t __index = 0;
  eState_t curState = eNone;
  eState_t lastState = eNone;
  bool lanChange = false;
  bool _isFlash = false;
  uint16_t getWordLen();
  virtual uint8_t readACK()= 0;
  void sendPack(uint8_t cmd,uint8_t* data =NULL,uint16_t len = 0);
  sSubMess_t getSubMess(const void *data);
  virtual uint8_t sendCommand(uint8_t *data,uint8_t length)=0;
  virtual uint8_t sendCommand(uint8_t *head,uint8_t *data,uint16_t length)=0;

};


class DFRobot_SpeechSynthesis_I2C :public DFRobot_SpeechSynthesis{
public:
  /**
   * @fn DFRobot_SpeechSynthesis_I2C
   * @brief Constructor
   * @param pWire I2C BUS pointer object， construct device, can pass parameter or not, default to Wire
   * @param address 7bits I2C address, the first three bits determine the value of the address, default to 0x50
   */
  DFRobot_SpeechSynthesis_I2C(uint8_t address = I2C_ADDR);
  ~DFRobot_SpeechSynthesis_I2C();
  /**
   * @fn begin
   * @brief init function
   */
  void begin();
private:
  uint8_t _deviceAddr;
  //Stream none;
  uint8_t readACK();
  uint8_t sendCommand(uint8_t *data,uint8_t length);
  uint8_t sendCommand(uint8_t *head,uint8_t *data,uint16_t length);
};


class DFRobot_SpeechSynthesis_UART :public DFRobot_SpeechSynthesis{
public:
  /**
   * @fn DFRobot_SpeechSynthesis_UART
   * @brief Constructor
   */
  DFRobot_SpeechSynthesis_UART();
  /**
   * @fn begin
   * @brief init function
   */
  bool begin();

private:
  uint8_t readACK();
  uint8_t sendCommand(uint8_t *data,uint8_t length);
  uint8_t sendCommand(uint8_t *head,uint8_t *data,uint16_t length);

  uint32_t _baudRate;
};

DFRobot_SpeechSynthesis::DFRobot_SpeechSynthesis()
{

}

void DFRobot_SpeechSynthesis::speakElish(std::string word)
{
  uint16_t point = 0;
  _len = word.length();DBG(_len);
  _unicode = (uint8_t*)malloc(_len + 1);
  while (_index < _len) {
    _unicode[point++] = (word[_index] & 0x7f);
    _index++;
  }
  sendPack(START_SYNTHESIS1, _unicode, _len);

  wait();

  _index = 0;
  _len = 0;

  if (_unicode != NULL) {
    free(_unicode);
    _unicode = NULL;
  }
}
void DFRobot_SpeechSynthesis::setVolume(uint8_t voc)
{
  std::string str = "[v3]";
  if (voc > 9) voc = 9;
  str[2] = 48 + voc;
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setSpeed(uint8_t speed)
{
  std::string str = "[s5]";
  if (speed > 9) speed = 9;
  str[2] = 48 + speed;
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setTone(uint8_t tone)
{
  std::string str = "[t5]";
  if (tone > 9) tone = 9;
  str[2] = 48 + tone;
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setSoundType(eSoundType_t type)
{
  std::string str;
  if (type == eFemale1) {
    str = "[m3]";
  } else if (type == eMale1) {
    str = "[m51]";
  } else if (type == eMale2) {
    str = "[m52]";
  } else if (type == eFemale2) {
    str = "[m53]";
  } else if (type == eDonaldDuck) {
    str = "[m54]";
  } else if (type == eFemale3) {
    str = "[m55]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setEnglishPron(eENpron_t pron)
{
  std::string str;
  if (pron == eAlphabet) {
    str = "[h1]";
  } else if (pron == eWord) {
    str = "[h2]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setDigitalPron(eDigitalPron_t pron)
{
  std::string str;
  if (pron == eNumber) {
    str = "[n1]";
  } else if (pron == eNumeric) {
    str = "[n2]";
  } else if (pron == eAutoJudged) {
    str = "[n0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setSpeechStyle(eSpeechStyle_t style)
{
  std::string str;
  if (style == eCaton) {
    str = "[f0]";
  } else if (style == eSmooth) {
    str = "[f1]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::enablePINYIN(bool enable)
{
  std::string str;
  if (enable == true) {
    str = "[i1]";
  } else if (enable == false) {
    str = "[i0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setLanguage(eLanguage_t style)
{
  std::string str;
  if (style == eChinesel) {
    str = "[g1]";
  } else if (style == eEnglishl) {
    str = "[g2]";
  } else if (style == eAutoJudgel) {
    str = "[g0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setZeroPron(eZeroPron_t pron)
{
  std::string str;
  if (pron == eZreo) {
    str = "[o0]";
  } else if (pron == eOu) {
    str = "[o1]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::setOnePron(eOnePron_t pron)
{
  std::string str;
  if (pron == eYao) {
    str = "[y0]";
  } else if (pron == eChone) {
    str = "[y1]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::setNamePron(eNamePron_t pron)
{
  std::string str;
  if (pron == eName) {
    str = "[r1]";
  } else if (pron == eAutoJudgedn) {
    str = "[r0]";
  }
  speakElish(str);
  DBG(str);
}

void DFRobot_SpeechSynthesis::enableRhythm(bool enable)
{
  std::string str;
  if (enable == true) {
    str = "[z1]";
  } else if (enable == false) {
    str = "[z0]";
  }
  speakElish(str);
  DBG(str);
}
void DFRobot_SpeechSynthesis::reset()
{

  speakElish("[d]");

}

void DFRobot_SpeechSynthesis::speak(std::string word)
{
  //DBG("String");
  uint32_t uni = 0;
  uint8_t utf8State = 0;
  DBG("\n");
  uint16_t point = 0;
  if (_utf8 != NULL) {
    free(_utf8);
    _utf8 = NULL;
  }DBG("\n");
  _len = word.length(); //总长度
  _utf8 = (uint8_t*)malloc(_len + 1);
  if (_utf8 == NULL) {
    DBG("no memory");
    return;
  }
  DBG("_len=");DBG(_len);

  for (uint32_t i = 0;i <= _len;i++) {
    _utf8[i] = word[i]; //总的utf8码
    //DBG(_utf8[i]);
  }
  DBG("\n");
  word = "";
  uint16_t len1 = getWordLen();
  DBG("len1=");DBG(len1);
  _unicode = (uint8_t*)malloc(len1 + 1);
  while (_index < _len) {
    if (_utf8[_index] >= 0xfc) {
      utf8State = 5;
      uni = _utf8[_index] & 1;
      _index++;
      for (uint8_t i = 1;i <= 5;i++) {
        uni <<= 6;
        uni |= (_utf8[_index] & 0x3f);
        utf8State--;
        _index++;
      }

    } else if (_utf8[_index] >= 0xf8) {
      utf8State = 4;
      uni = _utf8[_index] & 3;
      _index++;
      for (uint8_t i = 1;i <= 4;i++) {
        uni <<= 6;
        uni |= (_utf8[_index] & 0x03f);
        utf8State--;
        _index++;
      }

    } else if (_utf8[_index] >= 0xf0) {
      utf8State = 3;
      uni = _utf8[_index] & 7;
      _index++;
      for (uint8_t i = 1;i <= 3;i++) {
        uni <<= 6;
        uni |= (_utf8[_index] & 0x03f);
        utf8State--;
        _index++;
      }
      DBG(_index);DBG(uni);

    } else if (_utf8[_index] >= 0xe0) {
      curState = eChinese;
      if ((curState != lastState) && (lastState != eNone)) {
        lanChange = true;
      } else {
        utf8State = 2;
        DBG("index=");DBG(_index);
        uni = _utf8[_index] & 15;
        _index++;
        DBG("uni=");DBG(uni);
        for (uint8_t i = 1;i <= 2;i++) {
          uni <<= 6;
          uni |= (_utf8[_index] & 0x03f);
          utf8State--;
          _index++;
        }
        if (_utf8[_index] == 239) {
          //DBG("aaaa");
          lanChange = true;
        }
        lastState = eChinese;
        DBG(_index);DBG(uni);
        _unicode[point++] = uni & 0xff;
        _unicode[point++] = uni >> 8;
        //if(point ==  24) lanChange = true;
      }
    } else if (_utf8[_index] >= 0xc0) {
      curState = eChinese;
      if ((curState != lastState) && (lastState != eNone)) {
        lanChange = true;

      } else {
        utf8State = 1;
        uni = _utf8[_index] & 0x1f;
        _index++;
        for (uint8_t i = 1;i <= 1;i++) {
          uni <<= 6;
          uni |= (_utf8[_index] & 0x03f);
          utf8State--;
          _index++;
        }
        lastState = eChinese;
        _unicode[point++] = uni & 0xff;
        _unicode[point++] = uni >> 8;
        //if(point ==  24) lanChange = true;
      }
    } else if (_utf8[_index] <= 0x80) {
      curState = eEnglish;
      if ((curState != lastState) && (lastState != eNone)) {
        lanChange = true;

      } else {
        _unicode[point++] = (_utf8[_index] & 0x7f);
        _index++;
        lastState = eEnglish;
        if (/*(point ==  24) || */(_utf8[_index] == 0x20) || (_utf8[_index] == 0x2c)) lanChange = true;
      }
    }
    if (lanChange == true) {
      if (lastState == eChinese) {
        sendPack(START_SYNTHESIS, _unicode, point);
        wait();
      } else if (lastState == eEnglish) {
        sendPack(START_SYNTHESIS1, _unicode, point);
        wait();
      }
      lastState = eNone;
      curState = eNone;
      point = 0;
      lanChange = false;
    }
  }
  if (lastState == eChinese) {
    sendPack(START_SYNTHESIS, _unicode, point);
    wait();
  } else if (lastState == eEnglish) {
    sendPack(START_SYNTHESIS1, _unicode, point);
    wait();
  }
  lastState = eNone;
  curState = eNone;
  point = 0;
  lanChange = false;

  _index = 0;
  _len = 0;

  if (_unicode != NULL) {
    free(_unicode);
    _unicode = NULL;
  }
  return;

}
void DFRobot_SpeechSynthesis::wait()
{
  while (readACK() != 0x41)//等待语音合成完成
  {
    //if(readACK() == 0) break;
#if (defined ESP8266)
    yield();
#endif
  }
  //DBG("NEXT--------------------------------0X41")
  delay(100);

  while (1)//等待语音播放完成
  {
    //delay(20);
    uint8_t check[4] = { 0xFD,0x00,0x01,0x21 };
    sendCommand(check, 4);
#if (defined ESP8266)
    yield();
#endif
    if (readACK() == 0x4f) break;
    delay(20);
  }

  /*
readACK();
readACK();
readACK();
readACK();

*/

}
uint16_t DFRobot_SpeechSynthesis::getWordLen()
{
  uint16_t index = 0;
  uint32_t uni = 0;
  uint16_t length = 0;DBG("\n");
  DBG("len=");DBG(_len);
  while (index < _len) {
    DBG("index=");DBG(index);
    if (_utf8[index] >= 0xfc) {
      index++;
      for (uint8_t i = 1;i <= 5;i++) {
        index++;
      }
      length += 4;
    } else if (_utf8[index] >= 0xf8) {
      index++;
      for (uint8_t i = 1;i <= 4;i++) {
        index++;
      }
      length += 3;
    } else if (_utf8[index] >= 0xf0) {
      index++;
      for (uint8_t i = 1;i <= 3;i++) {
        index++;
      }
      length += 3;
    } else if (_utf8[index] >= 0xe0) {
      index++;
      for (uint8_t i = 1;i <= 2;i++) {
        index++;
      }
      length += 2;
    } else if (_utf8[index] >= 0xc0) {

      index++;
      for (uint8_t i = 1;i <= 1;i++) {
        index++;
      }
      length += 2;
    } else if (_utf8[index] <= 0x80) {
      index++;
      length++;
    }
  }
  return length;
}
void DFRobot_SpeechSynthesis::speak(const char* data)
{

  sSubMess_t mess;
  mess.index = 0;
  uint16_t uni = 0;
  __index = 0;
  uint8_t* _data = (uint8_t*)data;
  while (pgm_read_byte(_data + _len) != 0) {
    _len++;
  }
  while (__index < _len) {
    _isFlash = true;
    mess = getSubMess(_data);
    if (mess.ischar == 2) {
      uint8_t sendData[5] = { 0xfd,(mess.length + 2) >> 8,(mess.length + 2) & 0xff,0x01,0x03 };
      sendCommand(sendData, 5);
      for (uint16_t i = 0; i < mess.index;) {
        uint8_t utf8 = pgm_read_byte(_data + __index + i);
        if (utf8 >= 0xe0) {
          uni = utf8 & 15;
          i++;
          utf8 = pgm_read_byte(_data + __index + i);
          uni <<= 6;
          uni |= (utf8 & 0x03f);
          i++;
          utf8 = pgm_read_byte(_data + __index + i);
          uni <<= 6;
          uni |= (utf8 & 0x03f);

          sendData[0] = uni & 0xff;
          sendData[1] = uni >> 8;
          sendCommand(sendData, 2);
          i++;
        } else if (utf8 >= 0xc0) {
          uni = utf8 & 0x1f;
          i++;
          utf8 = pgm_read_byte(_data + __index + i);
          uni <<= 6;
          uni |= (utf8 & 0x03f);
          i++;
          sendData[0] = uni & 0xff;
          sendData[1] = uni >> 8;
          sendCommand(sendData, 2);
        }

      }
    }

    if (mess.ischar == 1) {
      uint8_t sendData[5] = { 0xfd,(mess.length + 2) >> 8,(mess.length + 2) & 0xff,0x01,0x00 };
      sendCommand(sendData, 5);
      for (uint16_t i = 0; i < mess.index;) {
        uint8_t utf8 = pgm_read_byte(_data + __index + i);
        sendData[0] = utf8 & 0x7f;
        sendCommand(sendData, 1);
        i++;
      }
    }
    if (mess.length == 0) break;
    wait();

    __index += mess.index;
  }


}

DFRobot_SpeechSynthesis::sSubMess_t DFRobot_SpeechSynthesis::getSubMess(const void* data)
{

  uint16_t index = 0;
  sSubMess_t mess;
  uint16_t length = 0;
  uint8_t* _data = (uint8_t*)data;
  if (_isFlash == true) {
    while (pgm_read_byte(_data + _len) != 0) {
      _len++;
    }
  } else {
    _len = strlen((char*)_data);
  }
  bool frist = false;
  uint8_t ischar = 0;
  while (index < _len) {
    uint8_t utf8;
    if (_isFlash == true) {
      utf8 = pgm_read_byte(_data + index + __index);
    } else {
      utf8 = _data[index + __index];
    }
    if (utf8 >= 0xfc) {
      index += 6;
      length += 4;
    } else if (utf8 >= 0xf8) {
      index += 5;
      length += 3;
    } else if (utf8 >= 0xf0) {
      index += 4;
      length += 3;
    } else if (utf8 >= 0xe0) {
      if (ischar == 1) {
        break;
      }
      index += 3;
      length += 2;
      if (frist == false) {
        ischar = 2;
        frist = true;
      }
    } else if (utf8 >= 0xc0) {
      if (ischar == 1) {
        break;
      }
      index += 2;
      length += 2;
      if (frist == false) {
        ischar = 2;
        frist = true;
      }
    } else  if (utf8 <= 0x80) {
      if (utf8 == 0) break;
      if (ischar == 2) {
        break;
      }

      index += 1;
      length++;

      if (frist == false) {
        ischar = 1;
        frist = true;
      }
    }
  }
  mess.ischar = ischar;
  mess.length = length;
  mess.index = index;
  return mess;
}

void DFRobot_SpeechSynthesis::speak(const void* data)
{
  sSubMess_t mess;
  mess.index = 0;
  uint16_t uni = 0;
  __index = 0;
  uint8_t* _data = (uint8_t*)data;
  uint16_t _len = strlen((char*)_data);
  while (__index < _len) {
    _isFlash = false;
    mess = getSubMess(_data);
    if (mess.ischar == 2) {
      uint8_t sendData[5] = { 0xfd,(mess.length + 2) >> 8,(mess.length + 2) & 0xff,0x01,0x03 };
      sendCommand(sendData, 5);
      for (uint16_t i = 0; i < mess.index;) {
        uint8_t utf8 = _data[__index + i];
        if (utf8 >= 0xe0) {
          uni = utf8 & 15;
          i++;
          utf8 = _data[__index + i];
          uni <<= 6;
          uni |= (utf8 & 0x03f);
          i++;
          utf8 = _data[__index + i];
          uni <<= 6;
          uni |= (utf8 & 0x03f);

          sendData[0] = uni & 0xff;
          sendData[1] = uni >> 8;
          sendCommand(sendData, 2);
          //
        //DBG(uni & 0xff,HEX);
          //DBG(uni >> 8,HEX);
          i++;
        } else if (utf8 >= 0xc0) {
          uni = utf8 & 0x1f;
          i++;
          utf8 = _data[__index + i];
          uni <<= 6;
          uni |= (utf8 & 0x03f);
          i++;
          sendData[0] = uni & 0xff;
          sendData[1] = uni >> 8;
          sendCommand(sendData, 2);
        }

      }
      //Wire.endTransmission();    // stop transmitting
    }

    if (mess.ischar == 1) {
      uint8_t sendData[5] = { 0xfd,(mess.length + 2) >> 8,(mess.length + 2) & 0xff,0x01,0x00 };
      sendCommand(sendData, 5);
      for (uint16_t i = 0; i < mess.index;) {
        uint8_t utf8 = _data[__index + i];
        sendData[0] = utf8 & 0x7f;
        sendCommand(sendData, 1);
        i++;
      }
    }
    if (mess.length == 0) break;
    wait();

    __index += mess.index;
  }
}
void DFRobot_SpeechSynthesis::stopSynthesis()
{
  sendPack(STOP_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::pauseSynthesis()
{
  sendPack(PAUSE_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::recoverSynthesis()
{
  sendPack(RECOVER_SYNTHESIS);
}
void DFRobot_SpeechSynthesis::sleep()
{
  sendPack(ENTERSAVEELETRI);
}
void DFRobot_SpeechSynthesis::wakeup()
{
  sendPack(WAKEUP);
}
void DFRobot_SpeechSynthesis::sendPack(uint8_t cmd, uint8_t* data, uint16_t len)
{

  uint16_t length = 0;
  uint8_t head[5] = { 0 };
  head[0] = 0xfd;
  switch (cmd) {
  case START_SYNTHESIS: {
    length = 2 + len;
    head[1] = length >> 8;
    head[2] = length & 0xff;
    head[3] = START_SYNTHESIS;
    head[4] = 0x03;
    sendCommand(head, data, len);
  } break;
  case START_SYNTHESIS1: {
    length = 2 + len;
    head[1] = length >> 8;
    head[2] = length & 0xff;
    head[3] = START_SYNTHESIS;
    head[4] = 0x04;
    sendCommand(head, data, len);
  }
                       break;
  default: {
    length = 1;
    head[1] = length >> 8;
    head[2] = length & 0xff;
    head[3] = cmd;
    sendCommand(head, 4);
  }
         break;
  }
}
DFRobot_SpeechSynthesis_I2C::DFRobot_SpeechSynthesis_I2C(uint8_t address)
{
  _deviceAddr = address;
}
DFRobot_SpeechSynthesis_I2C::~DFRobot_SpeechSynthesis_I2C()
{
  //_pWire->setClock(100000);
}

void DFRobot_SpeechSynthesis_I2C::begin()
{
  uint8_t ack = 0;

  beginTransmission(_deviceAddr);

  uint8_t init = 0xAA;
  for (uint8_t i = 0;i < 40;i++) {
    sendCommand(&init, 1);
//    APP_PRINT("HELLO\n");
    delay(50);
    uint8_t check[4] = { 0xFD,0x00,0x01,0x21 };
    sendCommand(check, 4);
//    APP_PRINT("BUNA\n");
    if (readACK() == 0x4f) break;

  }



  //delay(5000);

    //delay(50);
    //speakElish("[n1]");
  setVolume(1);
  //setSpeed(5);
 // setTone(5);

 // setEnglishPron(WORD);
}
uint8_t DFRobot_SpeechSynthesis_I2C::sendCommand(uint8_t* head, uint8_t* data, uint16_t length)
{
  DBG();
  uint16_t lenTemp = 0;
  beginTransmission(_deviceAddr);
  for (uint8_t i = 0;i < 5;i++) {
    write(head[i]);
    // Serial.print(head[i], HEX);
  }
  endTransmission(false);


  while (length) {
    if (length > 28) {
      lenTemp = 28;
    } else {
      lenTemp = length;
    }

    beginTransmission(_deviceAddr);
    for (uint8_t i = 0;i < lenTemp;i++) {
      write(data[i]);
      // Serial.print(data[i], HEX);
    }
//    if (endTransmission() != 0) {
//      DBG("ERR_DATA_BUS");
//      return ERR_DATA_BUS;
//    }
    endTransmission(false);
    length -= lenTemp;
    data += lenTemp;
  }
#ifdef ENABLE_DBG
  DBG();
  for (uint8_t i = 0;i < 5;i++) {
    Serial.print(head[i], HEX);
    Serial.print(" ");
  }
  for (uint8_t i = 0;i < length;i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  DBG();
#endif
  // if( _pWire->endTransmission() != 0 ) {
      // DBG("ERR_DATA_BUS");
      // return ERR_DATA_BUS;
  // }


  return ERR_OK;
}

uint8_t DFRobot_SpeechSynthesis_I2C::sendCommand(uint8_t* data, uint8_t length)
{
  beginTransmission(_deviceAddr);
  for (uint8_t i = 0;i < length;i++) {
    write(data[i]);
    // if (4 != length) {
    //   Serial.print(data[i], HEX);
    //   Serial.print(" ");
    // }
  }
//  if (endTransmission() != 0) {
//    DBG("ERR_DATA_BUS");
//    return ERR_DATA_BUS;
//  }

  endTransmission(false);

  return ERR_OK;
}
uint8_t DFRobot_SpeechSynthesis_I2C::readACK()
{

  uint8_t data = 0;
  requestFrom(_deviceAddr, 1);
  //delay(1);
  if (available()) {
    data = read();
  }
  // DBG(data, HEX);
  return data;
}

DFRobot_SpeechSynthesis_UART::DFRobot_SpeechSynthesis_UART()
{


}

bool DFRobot_SpeechSynthesis_UART::begin()
{
  if (NULL) {
    return false;
  } else {
    // speakElish("[n1]");
    setVolume(5);
    //setSpeed(5);
   // setTone(5);
   // setSoundType(eFemale1);
   // setEnglishPron(eWord);
    return true;
  }

}
uint8_t DFRobot_SpeechSynthesis_UART::sendCommand(uint8_t* head, uint8_t* data, uint16_t length)
{
  while (available()) {
    read();
  }


  for (uint8_t i = 0;i < 5;i++) {
    write(head[i]);
  }
  for (uint8_t i = 0;i < length;i++) {
    write(data[i]);
  }
#ifdef ENABLE_DBG
  DBG();
  for (uint8_t i = 0;i < 5;i++) {
    Serial.print(head[i], HEX);
    Serial.print(" ");
  }
  for (uint8_t i = 0;i < length;i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  DBG();
#endif
  return ERR_OK;
}

uint8_t DFRobot_SpeechSynthesis_UART::sendCommand(uint8_t* data, uint8_t length)
{
  for (uint8_t i = 0;i < length;i++) {
    write(data[i]);
  }
  return ERR_OK;
}
uint8_t DFRobot_SpeechSynthesis_UART::readACK()
{

  uint8_t data = 0;
  delay(10);
  //DBG(data,HEX);
  if (available()) {
    data = read();
    DBG(data, HEX);
  }
  DBG(data, HEX);
  return data;

}

#endif

