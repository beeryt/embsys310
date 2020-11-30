/*
 *  File:           rcc_ctrl.s
 *  Author:         Carl B. Smiley
 *  Date:           Nov 21 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    Assembly language function for enabling RCC using bit-banding
 */
    PUBLIC enable_rcc   // this function is available to the linker

    // .text:   The text section is used for keeping the actual code
    // CODE:    Interprets subsequent instructions as Arm/Thumb
    // REORDER: Starts a new section with the given name
    // NOROOT:  linker should discard this section if unused
    // (2):     align section to the second power of 2 (4 byte alignment)
    SECTION .text:CODE:REORDER:NOROOT(2)
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions

/**
 * Assembly language function for enabling RCC using bit-banding
 * note: bit-band aliases are found at base 0x4200.0000
 * note: bit-band address formula: (BASE + (BYTE * 32) + (BIT * 4))
 *
 * void enable_rcc(uint32_t port);
 *
 * \param port (R0)     indicates which port to enable the clock for
 */
enable_rcc

  END