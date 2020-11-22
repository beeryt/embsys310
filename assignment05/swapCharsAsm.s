/*
 *  File:           swapCharsAsm.s
 *  Author:         Carl B. Smiley
 *  Date:           Nov 21 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    take two char variables as input and swap the chars
 *                  BONUS: return 0 if the two chars match; otherwise return 1
 */

    PUBLIC swapCharsAsm         // this function is available to the linker

    // .text:   The text section is used for keeping the actual code
    // CODE:    Interprets subsequent instructions as Arm/Thumb
    // REORDER: Starts a new section with the given name
    // NOROOT:  linker should discard this section if unused
    // (2):     align section to the second power of 2 (4 byte alignment)
    SECTION .text:CODE:REORDER:NOROOT(2)
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions

/**
 * Takes as input two char addresses and swaps the chars within
 *
 * void swapCharsAsm(char*, char*);
 *
 * \param charA (R0)
 * \param charB (R1)
 * \returns 0 if `charA == charB`; otherwise 1
 */
swapCharsAsm
    LDRB        R2, [R0]        // load byte (char) from charA address
    LDRB        R3, [R1]        // load byte (char) from charB address

    CMP         R2, R3          // compare bytes (stored until BEQ below)

    // perform in-place XOR swap
    EOR         R2, R2, R3      // *charA ^= *charB
    EOR         R3, R3, R2      // *charB ^= *charA
    EOR         R2, R2, R3      // *charA ^= *charA

    STRB        R2, [R0]        // store byte (char) back to charA address
    STRB        R3, [R1]        // store byte (char) back to charB address

    MOV         R0, #0          // assume a 0 return
    BEQ         done            // if ASPR is EQ then skip next instruction
    MOV         R0, #1          // ASPR was NE, return 1

done:
    BX          LR              // branch back to caller
    END