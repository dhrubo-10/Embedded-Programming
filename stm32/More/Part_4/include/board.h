#ifndef BOARD_H
#define BOARD_H

#include "stm32f1xx_hal.h"
extern UART_HandleTypeDef huart1;

// PC13 LED is active low: RESET = on, SET = off 
#define LED_ON()   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)
#define LED_OFF()  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)

/* HAL_Init + 72 MHz clock + PC13 as output */
void board_init(void);
/* Stops the CPU so a debugger can see where it died. */
void Error_Handler(void);
#endif 