/*
 *  File:           main.c
 *  Author:         Carl B. Smiley
 *  Date:           Nov 30 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    Blink code using externally linked assembly functions
 */
#include <stdint.h>

#define RCC_BASE                0x40021000
#define RCC_AHB2ENR             (*((unsigned int*)(RCC_BASE + 0x4C)))

#define GPIOA_BASE              0x48000000
#define GPIOA_MODER             (*((unsigned int*)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR               (*((unsigned int*)(GPIOA_BASE + 0x14)))

#define GPIOAEN_POS             0
#define GPIOAEN                 (1<<GPIOAEN_POS)
#define ORD5                    (1<<5)
#define GPIO_MODER_MODE5_0      (0x1<<10)
#define GPIO_MODER_MODE5_1      (0x2<<10)

#define LED_ON 1
#define LED_OFF 0
#define DELAY_DURATION 100000

void delay(uint32_t iteration);
void control_user_led1(uint8_t state, uint32_t duration);
void enable_rcc(uint32_t port);

void main(void)
{
    // enable GPIOA peripheral clock
#if defined(PROBLEM3)
    enable_rcc(GPIOAEN_POS);
#else
    RCC_AHB2ENR |= GPIOAEN;
#endif

    // enable PA5 output mode (shortcut when starting at reset value)
    GPIOA_MODER &= ~GPIO_MODER_MODE5_1;

    // blink LED1 using asssembly function
    while(1)
    {
      control_user_led1(LED_ON, DELAY_DURATION);
      control_user_led1(LED_OFF, DELAY_DURATION);
    }
}
