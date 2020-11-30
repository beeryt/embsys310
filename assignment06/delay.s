/*
 *  File:           delay.s
 *  Author:         Carl B. Smiley
 *  Date:           Nov 29 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    Assembly language function for basic busy wait
 */
    PUBLIC delay        // this function is available to the linker

    // .text:   The text section is used for keeping the actual code
    // CODE:    Interprets subsequent instructions as Arm/Thumb
    // REORDER: Starts a new section with the given name
    // NOROOT:  linker should discard this section if unused
    // (2):     align section to the second power of 2 (4 byte alignment)
    SECTION .text:CODE:REORDER:NOROOT(2)
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions

/**
 * Assembly language function for basic busy wait
 *
 * void delay(uint32_t iteration);
 *
 * \param iteration (R0)        number of loops to delay
 */
delay

  END