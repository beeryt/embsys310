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
#define RCC_AHB2ENR_ADDR (RCC_AHB2ENR_BASE + 0x4C)
#define RCC_AHB2ENR (*((unsigned int*)(RCC_AHB2ENR_ADDR)))
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x00)))
#define GPIOB_MODER (*((unsigned int*)(GPIOB_BASE + 0x00)))
#define GPIOA_ODR   (*((unsigned int*)(GPIOA_BASE + 0x14)))
#define GPIOB_ODR   (*((unsigned int*)(GPIOB_BASE + 0x14)))

// Macros for Bit Values
#define GPIOAEN_BIT     0
#define GPIOBEN_BIT     1
#define GPIOAEN         (1<<GPIOAEN_BIT)
#define GPIOBEN         (1<<GPIOBEN_BIT)
#define MODE5_0         (1<<10)
#define MODE5_1         (1<<11)
#define MODE15_0        (1<<28)
#define MODE14_1        (1<<29)
#define OD5             (1<<5)
#define OD14            (1<<14)

#define COUNTER_RESET   (100000)

#define USE_BIT_BANDING
#define PERIPHERAL_BIT_BAND(ADDR, BIT) (*((unsigned int*)(0x42000000 + ((ADDR - 0x40000000) * 32) + (BIT * 4))))
#define SRAM_BIT_BAND(ADDR, BIT) (*((unsigned int*)(0x22000000 + ((ADDR - 0x20000000) * 32) + (BIT * 4))))

int main() {
  // sets up LED2 (PB14) as a GPIO output
#ifdef USE_BIT_BANDING
  PERIPHERAL_BIT_BAND(RCC_AHB2ENR_ADDR, GPIOAEN_BIT) = 1;
  PERIPHERAL_BIT_BAND(RCC_AHB2ENR_ADDR, GPIOBEN_BIT) = 1;
#else
  RCC_AHB2ENR   |= (GPIOAEN | GPIOBEN); // enable GPIOA and GPIOB
#endif
  GPIOA_MODER   &= ~MODE5_1;            // enable output for PA5 from reset state
  GPIOB_MODER   &= ~MODE14_1;           // enable output for PB14 from reset state
  GPIOB_ODR     |= OD14;                // turn on LED2 at PB14

  // blinks LED1 (PA5) indefinitely
  int counter = 0;
  while (1) {
    if (++counter > COUNTER_RESET) {
      GPIOA_ODR ^= OD5;
      counter = 0;
    }
  }
}
