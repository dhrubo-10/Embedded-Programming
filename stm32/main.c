#include <stdint.h>

/* RCC */
#define RCC_BASE        0x40021000U
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))

/* GPIOC */
#define GPIOC_BASE      0x40011000U
#define GPIOC_CRH       (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

#define RCC_APB2ENR_IOPCEN  (1U << 4)
#define PC13                (1U << 13)

static void delay(volatile uint32_t n) {
    while (n--) {
        __asm__("nop");
    }
}

int main(void) {
    /* enable GPIOC clock */
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* PC13: output push-pull 10MHz — CRH bits [23:20] = 0b0001 */
    GPIOC_CRH &= ~(0xFU << 20);
    GPIOC_CRH |=  (0x1U << 20);

  while (1) {
        GPIOC_ODR ^= PC13;
        delay(1000000);
    }
}