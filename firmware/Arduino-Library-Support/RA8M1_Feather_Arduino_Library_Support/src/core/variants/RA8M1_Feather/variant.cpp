#include "../../cores/arduino/Arduino.h"
#include "pinmux.h"
#include "pins_arduino.h"

const uint16_t P014_b[] = {
PIN_DAC|CHANNEL_0,
PIN_ANALOG | CHANNEL_7 | LAST_ITEM_GUARD
};
#define P014 P014_b

extern "C" const PinMuxCfg_t g_pin_cfg[] = { 
  { BSP_IO_PORT_04_PIN_10,    P410   }, /* (0) MISO  -------------------------  DIGITAL  */
  { BSP_IO_PORT_04_PIN_11,    P411   }, /* (1) MOSI  */
  { BSP_IO_PORT_04_PIN_12,    P412   }, /* (2) SCK  */
  { BSP_IO_PORT_02_PIN_05,    P205   }, /* (3) SCL */
  { BSP_IO_PORT_02_PIN_06,    P206   }, /* (4) SDA  */
  { BSP_IO_PORT_04_PIN_08,    P408   }, /* (5) D5 */
  { BSP_IO_PORT_04_PIN_14,    P414   }, /* (6) D6 */
  { BSP_IO_PORT_08_PIN_01,    P801   }, /* (7) TX  */
  { BSP_IO_PORT_08_PIN_02,    P802   }, /* (8) RX  */
  { BSP_IO_PORT_04_PIN_15,    P415   }, /* (9) D9  */
  { BSP_IO_PORT_01_PIN_12,    P112   }, /* (10) D10 */
  { BSP_IO_PORT_01_PIN_13,    P113   }, /* (11) D11 */
  { BSP_IO_PORT_01_PIN_14,    P114   }, /* (12) D12 */
  { BSP_IO_PORT_01_PIN_15,    P115   }, /* (13) D13 */
  { BSP_IO_PORT_00_PIN_00,    P000   }, /* (14) D14 */
  { BSP_IO_PORT_00_PIN_14,    P014   }, /* (15) A0  --------------------------  ANALOG  */
  { BSP_IO_PORT_00_PIN_08,    P008   }, /* (16) A1  */
  { BSP_IO_PORT_00_PIN_07,    P007   }, /* (17) A2  */
  { BSP_IO_PORT_00_PIN_06,    P006   }, /* (18) A3  */
  { BSP_IO_PORT_00_PIN_05,    P005   }, /* (19) A4  */
  { BSP_IO_PORT_00_PIN_04,    P004   }, /* (20) A5  */
};

extern "C" {
    unsigned int PINCOUNT_fn() {
        return (sizeof(g_pin_cfg) / sizeof(g_pin_cfg[0]));
    }
}

int32_t getPinIndex(bsp_io_port_pin_t p) {
  int max_index = PINS_COUNT;
  int rv = -1;
  for(int i = 0; i < max_index; i++) {
    if(g_pin_cfg[i].pin == p) {
      rv = i;
      break;
    }
  }
  return rv;
}


#include "FspTimer.h"
/*
void usb_post_initialization() {
  ((R_USB_FS0_Type*)R_USB_FS0_BASE)->USBMC_b.VDCEN = 1;
}

void enableSubclockInputPins() {
  R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
  R_SYSTEM->SOSCCR_b.SOSTP = 1;
  R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);
}
*/


void initVariant() {
  // bootloader configures LED_BUILTIN as PWM output, deconfigure it to avoid spurious signals
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  FspTimer::set_initial_timer_channel_as_pwm(GPT_TIMER, GET_CHANNEL(getPinCfgs(6, PIN_CFG_REQ_PWM)[0]));
  FspTimer::set_initial_timer_channel_as_pwm(GPT_TIMER, GET_CHANNEL(getPinCfgs(9, PIN_CFG_REQ_PWM)[0]));
  FspTimer::set_initial_timer_channel_as_pwm(GPT_TIMER, GET_CHANNEL(getPinCfgs(10, PIN_CFG_REQ_PWM)[0]));
  FspTimer::set_initial_timer_channel_as_pwm(GPT_TIMER, GET_CHANNEL(getPinCfgs(11, PIN_CFG_REQ_PWM)[0]));
  FspTimer::set_initial_timer_channel_as_pwm(GPT_TIMER, GET_CHANNEL(getPinCfgs(12, PIN_CFG_REQ_PWM)[0]));
  FspTimer::set_initial_timer_channel_as_pwm(GPT_TIMER, GET_CHANNEL(getPinCfgs(13, PIN_CFG_REQ_PWM)[0]));
}
