/*
 *  File:           main.c
 *  Author:         Carl B. Smiley
 *  Date:           Nov 20 2020
 *  Course:         Fundamentals of Embedded and Real Time Systems
 *
 *  Description:    implementations for "main" function for each problem
 */

#include <assert.h>

// Function declarations of functions used in all problems
void swap_pointers(void** ptrA, void** ptrB);       // used in problem1
int divAsm(int a);                                  // used in problem2
void swapCharsAsm(char a, char b);                  // used in problem3
void swapPointersAsm(void** ptrA, void** ptrB);     // used in problem4

// Function declarations for "main" function for each problem
int problem1_main();
int problem2_main();
int problem3_main();
int problem4_main();

int main() {
#if defined(PROBLEM1)
    return problem1_main();
#elif defined(PROBLEM2)
    return problem2_main();
#elif defined(PROBLEM3)
    return problem3_main();
#elif defined(PROBLEM4)
    return problem4_main();
#else
    return 1; // set which problem will run using compiler define: `-DPROBLEM1`
#endif
}

void swap_pointers(void** ptrA, void** ptrB) {
    void* tmp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = tmp;
}

int problem1_main() {
    int A = 1;
    int B = 2;
    int *ptrA = &A;
    int *ptrB = &B;

    int *originalA = ptrA;
    int *originalB = ptrB;

    swap_pointers((void*)&ptrA, (void*)&ptrB);

    assert(ptrA != ptrB);
    assert(A == *ptrB);
    assert(B == *ptrA);
    assert(originalA == ptrB);
    assert(originalB == ptrA);
    return 0;
}

int problem2_main() {
    return 0;
}

int problem3_main() {
    return 0;
}

int problem4_main() {
    return 0;
}