/*
 *  File:           divAsm.s
 *  Author:         Carl B. Smiley
 *  Date:           Nov 21 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    take an input, divide it by 2, and return the result
 */

    EXTERN myCstr       // this variable is defined elsewhere
    EXTERN PrintString  // this function is defined elsewhere

    PUBLIC divAsm       // this function is available to the linker

    // .text:   The text section is used for keeping the actual code
    // CODE:    Interprets subsequent instructions as Arm/Thumb
    // REORDER: Starts a new section with the given name
    // NOROOT:  linker should discard this section if unused
    // (2):     align section to the second power of 2 (4 byte alignment)
    SECTION .text:CODE:REORDER:NOROOT(2)
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions

/**
 * Takes an input argument, divides it by two, and returns the result
 *
 * int divAsm(int);
 *
 * \param R0    An 32-bit integer
 * \returns     R0 divided by two
 */
divAsm
  PUSH  {R0, LR}        // save the input argument and LR before calling PrintString

  LDR   R0, =myCstr     // load myCstr into R0 (char*)
  LDR   R0, [R0]        // load addres
  BL    PrintString

  POP   {R0, LR}        // restore input argument and LR after call to PrintString

  LSR   R0, R0, #1      // logical-shift-right is equivalent to divide-by-two
  BX    LR              // branch back to LR to "return" result
  END
