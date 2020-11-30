/*
 *  File:           user_led.s
 *  Author:         Carl B. Smiley
 *  Date:           Nov 29 2020
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
GPIOB_BASE  EQU 0x48000400
GPIO_ODR    EQU 0x14
GPIO_BIT_5  EQU (1<<5)
GPIO_BIT_14 EQU (1<<14)

/**
 * Assembly language function for controlling the user LED
 *
 * void control_user_led1(uint8_t state, uint32_t duration);
 *
 * \param state (R0)            whether LED should be ON(1) or OFF(0)
 * \param duration (R1)         how many cycles to delay for
 */
control_user_led1

  END