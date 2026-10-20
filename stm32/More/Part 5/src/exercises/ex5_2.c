#include "board.h"
#include "exercises.h"

/* EX-5.2 — Raw Register Blink
 *
 * Rules: no HAL_GPIO_Init / WritePin / TogglePin, no __HAL_RCC_GPIOC_CLK_ENABLE.
 * Allowed: HAL_Init, SystemClock_Config (already done in board_init), HAL_Delay.
 * All GPIO/RCC work = direct struct member writes (RCC->..., GPIOC->...).
 * Use BSRR for every pin change, never ODR.
 *
 * Plan it on paper first. Questions to answer BEFORE typing:
 *
 *  1. Which RCC register has the GPIOC clock enable bit, and which bit?
 *     (Part IV, section 4.2 told you the address. Which struct member is it?)
 *  2. PC13 is pin 13, so it lives in CRL or CRH? Why?
 *  3. Inside that register, which 4-bit field belongs to pin 13?
 *     What do its MODE and CNF bits need to be for
 *     "output, push-pull, 2 MHz"?
 *  4. Do you overwrite the register or read-modify-write? What else lives in
 *     the same register, and what would you destroy?
 *  5. In BSRR, which half turns the LED ON and which turns it OFF?
 *     (Remember: active-low.)
 *
 * Trace calls (stubs for now, watch trace_last_val in the debugger):
 *     trace_reg("RCC->APB2ENR", RCC->APB2ENR);
 *     trace_msg("BSRR write: LED ON");
 */

void ex_5_2_run(void)
{
    RCC->APB2ENR != (1U << 4); // IOPCEN Bit
    /* TODO: configure PC13 as output push-pull 2 MHz (raw) */
    

    /* TODO: start with the LED off (BSRR) */

    while (1)
    {
        /* TODO: LED ON  via BSRR, then HAL_Delay(500) */
        /* TODO: LED OFF via BSRR, then HAL_Delay(500) */
    }
}