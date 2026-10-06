/**
 * clock, GPIO, SysTick_Handler, Error_Handler
 */

#include "board.h"

void Error_Handler(void)
{
    __disable_irq();
    while (1) { }
}

static void SystemClock_Conf(void)
{
    RCC_OscInitTypeDef Osc_init = {0};
    RCC_ClkInitTypeDef Clk_init = {0};

    Osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    Osc_init.HSEState = RCC_HSE_ON;
    Osc_init.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    Osc_init.HSIState = RCC_HSI_ON;
    Osc_init.PLL.PLLState = RCC_PLL_ON;
    Osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    Osc_init.PLL.PLLMUL = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&Osc_init) != HAL_OK)
        Error_Handler();

    Clk_init.ClockType = RCC_CLOCKTYPE_HCLK |
                         RCC_CLOCKTYPE_SYSCLK |
                         RCC_CLOCKTYPE_PCLK1 |
                         RCC_CLOCKTYPE_PCLK2;

    Clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    Clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    Clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
    Clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&Clk_init, FLASH_LATENCY_2) != HAL_OK)
        Error_Handler();
}

static void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    LED_OFF();
}

void board_init(void)
{
    HAL_Init();
    SystemClock_Conf();
    GPIO_Init();
}

/* Must exist exactly once in the whole firmware. */
void SysTick_Handler(void)
{
    HAL_IncTick();
}