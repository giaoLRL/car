#ifndef __UART_PRINTF_H
#define __UART_PRINTF_H

#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_uart.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int uart_printf(const char *fmt, ...);
void uart_print_float(float value, uint8_t precision);
int remote_uart_printf(const char *fmt, ...);
#ifdef __cplusplus
}
#endif

#endif