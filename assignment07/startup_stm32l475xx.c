/*
 *  File:           startup_stm32l475xx.c
 *  Author:         Carl B. Smiley
 *  Date:           Nov 30 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    contains the vector table and Unused_Handler
 */
#include "stm32l4xx_it.h"

extern int CSTACK$$Limit;               // magic IAR syntax for CSTACK limit
extern void __iar_program_start(void);  // Reset_Handler should start here!

void Unused_Handler(void);              // primary handler for any unused vectors

const int __vector_table[] @ ".intvec" = {
    (int)&CSTACK$$Limit,
    (int)&__iar_program_start,
    (int)&NMI_Handler,
    (int)&HardFault_Handler,
    (int)&MemManage_Handler,
    (int)&BusFault_Handler,
    (int)&UsageFault_Handler,
    0,0,0,0,    // reserved
    (int)&SVC_Handler,
    (int)&DebugMon_Handler,
    0,          // reserved
    (int)&PendSV_Handler,
    (int)&SysTick_Handler
};


/**
 * Get stuck in a loop
 */
void Unused_Handler(void) {
  while (1);
}


/**
 * defines weak reference to Unused_Handler
 */
#pragma weak NMI_Handler        = Unused_Handler
#pragma weak HardFault_Handler  = Unused_Handler
#pragma weak MemManage_Handler  = Unused_Handler
#pragma weak BusFault_Handler   = Unused_Handler
#pragma weak UsageFault_Handler = Unused_Handler
#pragma weak SVC_Handler        = Unused_Handler
#pragma weak DebugMon_Handler   = Unused_Handler
#pragma weak PendSV_Handler     = Unused_Handler
#pragma weak SysTick_Handler    = Unused_Handler