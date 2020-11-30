/*
 *  File:           rcc_ctrl.s
 *  Author:         Carl B. Smiley
 *  Date:           Nov 30 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    Assembly language function for enabling GPIOA RCC clock
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

BB_BASE         EQU (0x42000000)
RCC_BASE        EQU (0x40021000)
RCC_AHB2ENR     EQU (RCC_BASE + 0x4C)

ALIAS_BASE      EQU (BB_BASE + ((RCC_AHB2ENR - 0x40000000) * 32))
ALIAS_BASE_H    EQU ((ALIAS_BASE>>16)&0xFFFF)
ALIAS_BASE_L    EQU (ALIAS_BASE&0xFFFF)

/**
 * Assembly language function for enabling GPIOA RCC clock using bit-banding
 * note: bit-band aliases are found at base 0x4200.0000
 * note: bit-band address formula: (BASE + (BYTE * 32) + (BIT * 4))
 *
 * void enable_rcc(uint32_t port);
 *
 * \param R0 (port)     indicates which port to enable the clock for
 */
enable_rcc:
  // calculate AHB2ENR bit-band alias
  //    register inputs:        R0 (port)
  //    registers modified:     R0, R1
  //
  MOV   R1, #4                  // calculate the word offset for specified bit
  MUL   R0, R0, R1              //      corresponds to (BIT * 4) in alias formula
  MOVW  R1, #ALIAS_BASE_L       // pre-calculated alias for AHB2ENR (bit 0)
  MOVT  R1, #ALIAS_BASE_H       //      32-bit immediate value loaded in 2 lines
  ADD   R1, R0, R1              // combine bit-banding alias for complete address
  MOV   R0, #1                  // load 1 into R1
  STR   R0, [R1]                // write 1 into bit-banding alias

  BX    LR                      // branch back to LR
  END