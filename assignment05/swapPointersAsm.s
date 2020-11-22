/*
 *  File:           swapPointersAsm.s
 *  Author:         Carl B. Smiley
 *  Date:           Nov 21 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    swap two pointers
 */

    PUBLIC swapPointersAsm      // this function is available to the linker

    // .text:   The text section is used for keeping the actual code
    // CODE:    Interprets subsequent instructions as Arm/Thumb
    // REORDER: Starts a new section with the given name
    // NOROOT:  linker should discard this section if unused
    // (2):     align section to the second power of 2 (4 byte alignment)
    SECTION .text:CODE:REORDER:NOROOT(2)
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions

/**
 * Takes as input two addresses two pointers and swaps the pointers'
 *
 * void swapPointersAsm(void** ptrA, void** ptrB);
 *
 * **Assumes `void*` is 32-bit wide!**
 *
 * \param ptrA (R0)
 * \param ptrB (R1)
 */
 swapPointersAsm:
    LDR         R2, [R0]        // load word (void*) from ptrA address
    LDR         R3, [R1]        // load word (void*) from ptrB address

    // perform in-place XOR swap
    EOR         R2, R2, R3      // *ptrA ^= *ptrB
    EOR         R3, R3, R2      // *ptrB ^= *ptrA
    EOR         R2, R2, R3      // *ptrA ^= *ptrB

    STR         R2, [R0]        // store word (void*) back to ptrA address
    STR         R3, [R1]        // store word (void*) back to ptrB address

    BX          LR              // branch back to caller
    END