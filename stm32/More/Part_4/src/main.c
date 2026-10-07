/**
 * main.c
 * Part IV: BLINK
 * Author: S. Dhrubo
 */
#include "board.h"
#include "exercises.h"

int main(void)
{
    board_init();
    // ex_4_1_run(); // ex4.1
    // ex_4_2_run(); // morse code ex4.2
    // char msg[] = "UART OK\r\n";
    // HAL_UART_Transmit(&huart1,
    //               (uint8_t *)msg,
    //               sizeof(msg) - 1,
    //               HAL_MAX_DELAY); // uart test
    ex_4_3_run();
    while (1) { }
}