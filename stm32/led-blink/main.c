#include <stdint.h>

/* RCC */
#define RCC_BASE            0x40021000U
#define RCC_APB2ENR         (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB2ENR_IOPAEN  (1U << 2)

/* GPIOA */
#define GPIOA_BASE          0x40010800U
#define GPIOA_CRL           (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR           (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))

#define PA1                 (1U << 1)

static void delay(volatile uint32_t n) {
    while (n--) {
        __asm__("nop");
    }
}

int main(void) {
    /* enable GPIOA clock */
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* PA1: output push-pull 10MHz. CRL bits [7:4] = 0b0001 */
    GPIOA_CRL &= ~(0xFU << 4);
    GPIOA_CRL |=  (0x1U << 4);

    while (1) {
        GPIOA_ODR ^= PA1;
        delay(1000000);
    }
}