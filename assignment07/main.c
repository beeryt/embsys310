/*
 *  File:           main.c
 *  Author:         Carl B. Smiley
 *  Date:           Nov 30 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    blinks using delay which implements SysTick timer
 */

#include "stm32l4xx_it.h"
#include "include/stm32l475xx.h"

// global counter for delay function.
volatile static uint32_t g_milliseconds_elapsed;

// Delay function which does a blocking (busy) wait for specified milliseconds
void delay(uint32_t milli);


int main() {
  // configure SysTick peripheral
  int status = SysTick_Config(4000000U / 1000); // startup clock is 4MHz / 1000 is 1ms
  if (status != 0) while (1); // infinite loop on failure

  // enable peripheral clock for GPIOA
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

  // enable PA5 output mode (shortcut when starting at reset value)
  GPIOA->MODER &= ~GPIO_MODER_MODE5_1;

  while (1) {
    // toggle PA5 and delay
    GPIOA->ODR ^= GPIO_ODR_OD5;
    delay(200);
  }
}


/**
 * SysTick timer interrupt handler. Increments global counter for delay function.
 */
void SysTick_Handler(void) {
  // note: gets overwritten to 0 at start of delay function
  g_milliseconds_elapsed++;
}


/**
 * Delay function which does a blocking (busy) wait for specified milliseconds
 *
 * \param milli         milliseconds to delay
 */
void delay(uint32_t milli) {
  g_milliseconds_elapsed = 0;                   // start global counter
  while (g_milliseconds_elapsed < milli);       // wait for global counter
}