/*
 *  File:           user_led.s
 *  Author:         Carl B. Smiley
 *  Date:           Nov 30 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    Assembly language function for controlling the user LED
 */

    EXTERN delay        // this variable is defined elsewhere
    EXTERN PrintString  // this function is defined elsewhere

    PUBLIC control_user_led1       // this function is available to the linker

    // .text:   The text section is used for keeping the actual code
    // CODE:    Interprets subsequent instructions as Arm/Thumb
    // REORDER: Starts a new section with the given name
    // NOROOT:  linker should discard this section if unused
    // (2):     align section to the second power of 2 (4 byte alignment)
    SECTION .text:CODE:REORDER:NOROOT(2)
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions

GPIOA_BASE  EQU 0x48000000
GPIO_ODR    EQU 0x14
GPIO_BIT_5  EQU (1<<5)

/**
 * Assembly language function for controlling the user LED
 *
 * void control_user_led1(uint8_t state, uint32_t duration);
 *
 * \param R0 (state)            whether LED should be LED_ON(1) or LED_OFF(0)
 * \param R1 (duration)         how many iterations to delay for
 */
control_user_led1
  // set LED1 state in GPIOA
  //    register inputs:        R0 (state)
  //    registers modified:     R0, R2, R3
  //
  LSL   R0, R0, #5              // prepare state for writing
  MOV   R2, #GPIOA_BASE         // load GPIOA_BASE into R2
  LDR   R3, [R2, #GPIO_ODR]     // read current value of GPIO_ODR
  AND   R3, R3, #~GPIO_BIT_5    // clear GPIO_BIT_5
  ORR   R3, R3, R0              // set GPIO_BIT_5 according to state
  STR   R3, [R2, #GPIO_ODR]     // write modified value of GPIO_ODR

  // send duration to delay function
  //    register inputs:        R1 (duration)
  //    registers modified:     R0
  //
  MOV   R0, R1                  // move duration into R0 parameter position
  PUSH  {LR}                    // save LR before calling subroutine
  BL    delay                   // call delay subroutine
  POP   {LR}                    // restore LR after subroutine

  BX    LR                      // branch back to LR
  END