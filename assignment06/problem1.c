/*
 *  File:           problem1.c
 *  Author:         Carl B. Smiley
 *  Date:           Nov 29 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    implementation for "main" function for problem1
 */

#include "include/stm32l475xx.h"

int main() {
  // enable peripheral clock for GPIOA and GPIOB
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN;

  // set output for pin5 on GPIOA and pin14 on GPIOB
  // note: MODEn is a 2-bit setting with desired value 0x1
  //            after reset MODEn has a value of 0x3
  // To acheive value 0x1 simply clear the high bit for MODE5 and MODE14
  GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
  GPIOB->MODER &= ~GPIO_MODER_MODE14_1;

  while (1) {
    // toggle pin5 and pin14 on GPIOA and GPIOB respectively
    GPIOA->ODR ^= GPIO_ODR_OD5;
    GPIOB->ODR ^= GPIO_ODR_OD14;

    // quick and dirty busy wait
    int counter = 1e6;
    while (counter--) {}
  }
}