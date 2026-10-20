#ifndef BOARD_H
#define BOARD_H

#include "stm32f1xx_hal.h"

void board_init(void);

/* Stops the CPU so a debugger can see where it died. */
void Error_Handler(void);

void trace_reg(const char *name, uint32_t value);
void trace_msg(const char *msg);

#endif