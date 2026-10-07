/**
 * clock, GPIO, SysTick_Handler, Error_Handler
 */

#include "board.h"

GPIO_InitTypeDef GPIO_InitStruct = {0};
UART_HandleTypeDef huart1;
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
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
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    LED_OFF();
}

static void UART_Init(void)
{
    /**
     * bluepill UART conv config:
     * p10->RX
     * p09 -> TX
     */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();
    /* PA9 */

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* P10 */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
        Error_Handler();
}

void board_init(void)
{
    HAL_Init();
    SystemClock_Conf();
    GPIO_Init();
    UART_Init();
}

/* Must exist exactly once in the whole firmware. */
void SysTick_Handler(void)
{
    HAL_IncTick();
}