#include "boot.h"


/* call this function when you want to force the board to go in bootloader */
void goBootloader() {
   R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_PRC1_UNLOCK;
   //BOOT_DOUBLE_TAP_DATA = DOUBLE_TAP_MAGIC;
   R_SYSTEM->VBTBKR0_b.VBTBKR = 0x35;
   R_SYSTEM->VBTBKR1_b.VBTBKR = 0x81;
   R_SYSTEM->VBTBKR2_b.VBTBKR = 0x73;
   R_SYSTEM->VBTBKR3_b.VBTBKR = 0x07;
   R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_LOCK;
   ((R_USB_FS0_Type*)R_USB_FS0_BASE)->SYSCFG_b.DPRPU = 0;
   NVIC_SystemReset();
   while (1); // WDT will fire here
}
