/*
 *  File:           main.c
 *  Author:         Carl B. Smiley
 *  Date:           Nov 30 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    blinks using delay which implements SysTick timer
 */

#include "include/stm32l475xx.h"

#define DELAY_DURATION 100000

void delay(uint32_t milli);

int main() {
  // enable peripheral clock for GPIOA
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

  // enable PA5 output mode (shortcut when starting at reset value)
  GPIOA->MODER &= ~GPIO_MODER_MODE5_1;

  while (1) {
    // toggle PA5 and delay
    GPIOA->ODR ^= GPIO_ODR_OD5;
    delay(DELAY_DURATION);
  }
}

void delay(uint32_t milli) {
  // TODO replace this dirty busy wait
  while (milli--) {}
}