#include "board.h"
#include "exercises.h"

/* EX-4.1 steps 1-3: edit these two numbers, rebuild, flash.
 *   step 1: 1000 / 1000   (1 Hz)
 *   step 2:  250 /  250   (2 Hz)
 *   step 3:   50 / 1000
 */
/*
    my testcases:
    #define ON_MS   250
    #define OFF_MS  250

    #define ON_MS   500
    #define OFF_MS  500

    #define ON_MS   1000
    #define OFF_MS  1000
*/

#define ON_MS   50
#define OFF_MS  1000

void ex_4_1_run(void)
{
    while (1)
    {
        LED_ON();
        HAL_Delay(ON_MS);
        LED_OFF();
        HAL_Delay(OFF_MS);
    }
}