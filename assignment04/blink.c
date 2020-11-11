/*
 *  File:       blink.c
 *  Author:     Carl B. Smiley
 *  Date:       Nov 11 2020
 *  Course:     Fundamentals of Embedded and Real Time Systems
 *
 * Description: blinks LED1 (PA5) at a visible rate using XOR and Bit-Banding
 */

// Base Addresses for peripherals from Table 19 in DS10969 Rev 5
#define RCC_AHB2ENR_BASE 0x40021000
#define GPIOA_BASE       0x48000000
#define GPIOB_BASE       0x48000400

// Macros for convenient register access
#define RCC_AHB2ENR (*((unsigned int*)(RCC_AHB2ENR_BASE + 0x4C)))
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x00)))
#define GPIOB_MODER (*((unsigned int*)(GPIOB_BASE + 0x00)))
#define GPIOA_ODR   (*((unsigned int*)(GPIOA_BASE + 0x14)))
#define GPIOB_ODR   (*((unsigned int*)(GPIOB_BASE + 0x14)))

// Macros for Bit Values
#define GPIOAEN         (1<<0)
#define GPIOBEN         (1<<1)
#define MODE5_0         (1<<10)
#define MODE5_1         (1<<11)
#define MODE15_0        (1<<28)
#define MODE14_1        (1<<29)
#define OD5             (1<<5)
#define OD14            (1<<14)

#define COUNTER_RESET   (100000)

int main() {
  // sets up LED2 (PB14) as a GPIO output
  RCC_AHB2ENR   |= (GPIOAEN | GPIOBEN); // enable GPIOA and GPIOB
  GPIOA_MODER   &= ~MODE5_1;            // enable output for PA5 from reset state
  GPIOB_MODER   &= ~MODE14_1;           // enable output for PB14 from reset state
  GPIOB_ODR     |= OD14;                // turn on LED2 at PB14

  // blinks LED1 (PA5) indefinitely
  int counter = 0;
  while (1) {
    if (++counter > COUNTER_RESET) {
      GPIOB_ODR ^= OD14;
      counter = 0;
    }
  }
}
