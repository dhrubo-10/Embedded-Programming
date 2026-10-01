/**
 * main.c
 * Program: Led Blink
 * Author: S. Dhrubo
 * BluePills built-in PC13 Led blinks at 1hz
 */

#include "stm32f1xx_hal.h"

// Configure system clock.
void SystemClock_Conf(void)
{
    RCC_OscInitTypeDef Osc_init = {0};
    RCC_ClkInitTypeDef Clk_init = {0};
    Osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    Osc_init.HSEState       = RCC_HSE_ON;
    Osc_init.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    Osc_init.HSIState       = RCC_HSI_ON;
    Osc_init.PLL.PLLState   = RCC_PLL_ON;
    Osc_init.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    Osc_init.PLL.PLLMUL     = RCC_PLL_MUL9;         // it gives us 72 mhz -> 8*9
    HAL_RCC_OscConfig(&Osc_init);
    Clk_init.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                           | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    Clk_init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    Clk_init.AHBCLKDivider  = RCC_SYSCLK_DIV1;  // HCLK = 72 mhz
    Clk_init.APB1CLKDivider = RCC_HCLK_DIV2;    // APB1 = 36 mhz
    Clk_init.APB2CLKDivider = RCC_HCLK_DIV1;    // APB2 = 72 mhz
    HAL_RCC_ClockConfig(&Clk_init, FLASH_LATENCY_2);
}

// configure PC13 as push & pull output
static void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_init = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enables clock before touching GPIO registers
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET); // set initial output state High

    // configuring PC13: Output, push pull, no pull resistor, 2mhz
    GPIO_init.Pin   = GPIO_PIN_13;
    GPIO_init.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_init.Pull  = GPIO_NOPULL;
    GPIO_init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_init);
}

int main(void)
{
    HAL_Init();
    SystemClock_Conf();
    GPIO_Init();
    while(1)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        HAL_Delay(500);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_Delay(500);
    }
    return 0;
}