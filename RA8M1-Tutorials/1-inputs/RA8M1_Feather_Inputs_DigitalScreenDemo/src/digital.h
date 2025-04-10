#ifndef _DIGITAL_H_
#define _DIGITAL_H_

#include "common_utils.h"

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

bool digitalRead(int pin);
bool digitalRead(int pin) {
    bsp_io_level_t readLevel;
    fsp_err_t      err;

    err = R_IOPORT_PinRead(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, &readLevel);
    if(FSP_SUCCESS != err) {
        __BKPT(0);
    }
    return (bool)readLevel;
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

#endif //_DIGITAL_H_
