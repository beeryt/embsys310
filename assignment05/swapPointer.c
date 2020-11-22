/*
 *  File:           swapPointer.c
 *  Author:         Carl B. Smiley
 *  Date:           Nov 20 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    swap two pointers
 */

/**
 * Swaps two pointers
 *
 * Behavior is undefined if using function pointers
 *
 * \param ptrA  data pointer
 * \param ptrB  data pointer
 */
void swap_pointers(void** ptrA, void** ptrB) {
    void* tmp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = tmp;
}