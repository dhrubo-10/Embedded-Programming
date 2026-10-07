/*

* EX-4.3 [H] — Heartbeat Pattern
*
* Implement a heartbeat LED pattern:
* Two quick flashes then a pause — like a real heartbeat.
*
* Pattern: ON(80ms) OFF(80ms) ON(80ms) OFF(900ms) — repeat
*
* Requirements:
* 1. The pattern timing must be configurable via #define constants.
* 2. Print to serial: "Heartbeat #N" after each complete beat.
* 3. Every 10 beats, print uptime: "Uptime: Ns"
*
*/
#include "board.h"
#include "exercises.h"
#include <stdio.h> // we need snprintf for the uart terminal msgs
#include <string.h>

#define BEAT_ON_1   80
#define BEAT_OFF_1  80
#define BEAT_ON_2   80
#define BEAT_OFF_2  900

void ex_4_3_run(void)
{
    uint32_t beat = 0;
    while(1)
    {
        LED_ON();
        HAL_Delay(BEAT_ON_1);
        
        LED_OFF();
        HAL_Delay(BEAT_OFF_1);
        
        LED_ON();
        HAL_Delay(BEAT_ON_2);
        
        LED_OFF();
        HAL_Delay(BEAT_OFF_2);
        beat++;
        char msg[32];
        snprintf(msg, sizeof(msg), "Heartbeat #%lu\r\n", (unsigned long)beat);
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        if(beat % 10 == 0)
        {
            uint32_t uptime = HAL_GetTick() / 1000; // bcs we need this in sec
            snprintf(msg, sizeof(msg), "Uptime %lus\r\n", (unsigned long)uptime);
            HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        }
    }
}