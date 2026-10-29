/*
 * EX-5.3 [H] — GPIO Configuration Decoder
 *
 * Write a function that reads and prints the full GPIO configuration.
 *
 * void print_gpio_config(GPIO_TypeDef *port, char port_name);
 *
 * Example output for GPIOC after configuring PC13:
 *
 *   GPIOC configuration:
 *
 *   PC8:  Input, Floating
 *   PC9:  Input, Floating
 *   PC10: Input, Floating
 *   PC11: Input, Floating
 *   PC12: Input, Floating
 *   PC13: Output 2MHz, Push-Pull  <-- this one changed
 *   PC14: Input, Floating
 *   PC15: Input, Floating
 *
 * Algorithm:
 *
 *   Read CRL for pins 0–7, CRH for pins 8–15.
 *   Extract 4 bits per pin.
 *   Decode MODE bits → input or output speed.
 *   Decode CNF bits  → push-pull/open-drain or floating/pull/analog.
 *   Print each pin.
 *
 * Test: call it before and after GPIO_Init(). Show the change.
 */

#include "board.h"
#include "exercises.h"
#include <stdio.h>

void print_gpio_config(GPIO_TypeDef *port, char port_name)
{
    uint32_t config;
    uint32_t mode;
    uint32_t cnf;
    printf("GPIO%c configuration:\n", port_name);
    for (int i = 0; i < 16; i++)
    {
        if (i < 8)
            config = (port->CRL >> (i * 4)) & 0xFU;
        else
            config = (port->CRH >> ((i - 8) * 4)) & 0xFU;
        mode = config & 0x3U;
        cnf = config >> 2 & 0x3U;
        if (mode == 0)
        {
            if (cnf == 0)
                printf("P%c%d: Input, Analog\n", port_name, i);
            else if (cnf == 1)
                printf("P%c%d: Input, Floating\n", port_name, i);
            else if (cnf == 2)
                printf("P%c%d: Input, Pull-up/Pull-down\n", port_name, i);
            else
                printf("P%c%d: Input, Reserved\n", port_name, i);
        }
        else
        {
            const char *speed;
            if (mode == 1)
                speed = "10MHz";
            else if (mode == 2)
                speed = "2MHz";
            else
                speed = "50MHz";

            if (cnf == 0)
                printf("P%c%d: Output %s, Push-Pull\n",
                       port_name, i, speed);
            else if (cnf == 1)
                printf("P%c%d: Output %s, Open-Drain\n",
                       port_name, i, speed);
            else if (cnf == 2)
                printf("P%c%d: Alternate-function Output %s, Push-Pull\n",
                       port_name, i, speed);
            else
                printf("P%c%d: Alternate-function Output %s, Open-Drain\n",
                       port_name, i, speed);
        }
    }
}

void ex_5_3_run(void)
{
    RCC->APB2ENR |= (1U << 4);
    print_gpio_config(GPIOC, 'C');
    GPIOC->CRH &= ~(0xFU << 20);
    GPIOC->CRH |= (0x2U << 20);
    print_gpio_config(GPIOC, 'C');
    GPIOC->BSRR = (1U << 13);

    while (1)
    {
        GPIOC->BSRR = (1U << 29);
        trace_msg("BSRR write: LED ON");
        HAL_Delay(DELAY);
        GPIOC->BSRR = (1U << 13);
        trace_msg("BSRR write: LED OFF");
        HAL_Delay(DELAY);
    }
}