#include "handler_thread.h"
#include <Arduino.h>
extern "C" {
#include "../../../extras/tinyusb/src/tusb.h"
#include "../../../extras/tinyusb/src/class/hid/hid_device.h"
//#include "../../../extras/tinyusb/src/class/audio/audio.h"
//#include "../../../extras/tinyusb/src/class/midi/midi.h"
#include "../../../extras/tinyusb/src/class/dfu/dfu.h"
}

extern const uint32_t __StackTop;
const uint32_t APPLICATION_VECTOR_TABLE_ADDRESS_RAM = (uint32_t)&__StackTop;

volatile uint32_t *irq_vector_table;

void startAgt(void);
void initVariant(void);

extern uint32_t __ROM_Start;
extern const fsp_vector_t __VECTOR_TABLE[];
extern const fsp_vector_t g_vector_table[];

#if FSP_PRIV_TZ_USE_SECURE_REGS

#define BSP_PRV_BITS_PER_WORD    (32)

void unsecure_registers() {

    /* Unprotect security registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

 #if !BSP_TZ_SECURE_BUILD
    /* Set the DMAC channels to secure access. */
    R_CPSCU->ICUSARC = ~R_CPSCU_ICUSARC_SADMACn_Msk;
 #endif

    /* Place all vectors in non-secure state unless they are used in the secure project. */
    uint32_t interrupt_security_state[BSP_ICU_VECTOR_MAX_ENTRIES / BSP_PRV_BITS_PER_WORD];
    memset(&interrupt_security_state, UINT8_MAX, sizeof(interrupt_security_state));

    for (size_t i = 0U; i < BSP_ICU_VECTOR_MAX_ENTRIES; i++)
    {
         /* This is a secure vector. Clear the associated bit. */
         uint32_t index = i / BSP_PRV_BITS_PER_WORD;
         uint32_t bit   = i % BSP_PRV_BITS_PER_WORD;
         interrupt_security_state[index] &= ~(1U << bit);
    }

    /* The Secure Attribute managed within the ARM CPU NVIC must match the security attribution of IELSEn
     * (Reference section 13.2.9 in the RA6M4 manual R01UH0890EJ0050). */
    uint32_t volatile * p_icusarg = &R_CPSCU->ICUSARG;
    for (size_t i = 0U; i < BSP_ICU_VECTOR_MAX_ENTRIES / BSP_PRV_BITS_PER_WORD; i++)
    {
        p_icusarg[i]  = interrupt_security_state[i];
        NVIC->ITNS[i] = interrupt_security_state[i];
    }

    /* Protect security registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);
}
#endif

/* Handler Thread entry function */
/* pvParameters contains TaskHandle_t */
void handler_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    // Disable stack pointer protection
        // TODO: the best thing would be keeping SPMON active but changing
        // R_MPU_SPMON->SP[0].EA = __stack_top; on every call to malloc()
        // When stack and heap would collide, we could signal the NMI with mbed style leds patterns
     #if defined(__ARM_ARCH_8M_MAIN__) || defined(__ARM_ARCH_8M_BASE__)
        __set_MSPLIM(0);
     #if FSP_PRIV_TZ_USE_SECURE_REGS
        unsecure_registers();
     #endif
     #else
        R_MPU_SPMON->SP[0].CTL = 0;
     #endif


        __disable_irq();
        //irq_vector_table = (volatile uint32_t *)APPLICATION_VECTOR_TABLE_ADDRESS_RAM;
        size_t _i;
        for (_i=0; _i<BSP_CORTEX_VECTOR_TABLE_ENTRIES; _i++) {
           *(irq_vector_table + _i) = (uint32_t)__VECTOR_TABLE[_i];
        }

        for (_i=0; _i<BSP_ICU_VECTOR_MAX_ENTRIES; _i++) {
           *(irq_vector_table + _i +BSP_CORTEX_VECTOR_TABLE_ENTRIES) = (uint32_t)g_vector_table[_i];
        }

        SCB->VTOR = (uint32_t)irq_vector_table;

        __DSB();
        __enable_irq();


        R_BSP_PinAccessEnable();
        initVariant();
        analogReference();
        __USBStart();
        Serial.begin(115200);
        startAgt();

    /* TODO: add your own code here */
    while (1)
    {
        vTaskDelay (1);
    }
}

//Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (*func)()) {
   (void)func;
   return 0;
}

namespace __gnu_cxx {
   void __verbose_terminate_handler() { }
}
extern "C" __attribute__((weak)) void __cxa_pure_virtual(void);
extern "C" __attribute__((weak)) void __cxa_pure_virtual(void)
{
   exit(1);
}

