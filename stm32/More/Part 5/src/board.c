#include "board.h"

volatile const char *trace_last_msg = 0;
volatile uint32_t    trace_last_val = 0;
volatile uint32_t    trace_count    = 0;

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

void board_init(void)
{
    HAL_Init();
    SystemClock_Conf();
}

void trace_reg(const char *name, uint32_t value)
{
    trace_last_msg = name;
    trace_last_val = value;
    trace_count++;
}

void trace_msg(const char *msg)
{
    trace_last_msg = msg;
    trace_count++;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}