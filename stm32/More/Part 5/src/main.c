/* blink using raw register writes for GPIO */
#include "stm32f1xx_hal.h"
void SystemClock_Config(void);
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    // Enable GPIOC clock via RCC register
    RCC->APB2ENR |= (1U << 4);
    /*
     IOPCEN bit. now we need to configure PC13 as 2 MHz push pull output
    so .PC13 is in CRH. Bits for pin 13: [(13-8)*4 + 3 : (13-8)*4] =  [23:20]
    */
    GPIOC->CRH &= ~(0xFU << 20); // clear bits [23:20]
    GPIOC->CRH |= (0x2U << 20);
    /* MODE=10 (2MHz), CNF=00 (PP) (PC13 HIGH = LED off, active low)
     */
    GPIOC->BSRR = (1U << 13); // set PC13 HIGH
    /* its the blink loop */
    while (1)
    {
        GPIOC->BSRR = (1U << 29);
        HAL_Delay(500);
        GPIOC->BSRR = (1U << 13);
        HAL_Delay(500);
    }
}

void SystemClock_Config(void)
{
    /* here configure 72 MHz PLL from 8 MHz HSE */
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}