# EMBSYS 310 - Assignment 05
- [Problem 1](#Problem-1)
- [Problem 2](#Problem-2)
- [Problem 3](#Problem-3)
- [Problem 4](#Problem-4)

The [main.c](main.c) file contains the implementation for the `main()` function for each problem below.
Which problem is "selected" depends on the following compile-time definition: `-DPROBLEMN` where N is 1 through 4.
The compile-time definitions are already set up in the `iar/workspace.eww` IAR workspace.
However, if you need to manually set them up go to `Project > Options > C/C++ Compiler > Preprocessor > Defined symbols`.
Also check the `Preprocessor output to file` so switching projects will trigger a "rebuild".

```C
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
    // if using the `assignment05/iar/workspace.eww` then this is already set
#endif
}
```

---
## Problem 1
  > See [swapPointer.c](swapPointer.c) for implementation of `swap_pointer()`.<br>
  > See [main.c](main.c) for implementation of `problem1_main()`.
### 1.a Explain what the `main()` function does in order to setup the input arguments prior to calling the `swap_pointer()` function?
  > The declaration is `void swap_pointer(void**, void**)` since in order to swap pointers (and not their values) the *address* of the pointers must be passed into the swap function. I chose to use `void*` since it is guaranteed to hold any ***data*** pointer type (this will not work generically for function pointers).
  >
  > In the `main()` function in order to call `swap_pointer()` two things are needed:
  > 1. Get the address of the pointers: `&ptr`
  > 2. Cast to `void*` type: `(void*)&ptr`
  >
  > In the end this looks like `swap_pointer((void*)&ptrA, (void*)ptrB);`

  > In assembly this looks like:
  > ```asm
  > int problem1_main() {
  > problem1_main:
  > 0x800'0052: 0xb538         PUSH      {R3-R5, LR}
  > 0x800'0054: 0xb084         SUB       SP, SP, #0x10
  >  int A = 1;
  > 0x800'0056: 0x2001         MOVS      R0, #1
  > 0x800'0058: 0x9003         STR       R0, [SP, #0xc]
  >  int B = 2;
  > 0x800'005a: 0x2002         MOVS      R0, #2
  > 0x800'005c: 0x9002         STR       R0, [SP, #0x8]
  >  int *ptrA = &A;
  > 0x800'005e: 0xa803         ADD       R0, SP, #0xc
  > 0x800'0060: 0x9001         STR       R0, [SP, #0x4]
  >  int *ptrB = &B;
  > 0x800'0062: 0xa802         ADD       R0, SP, #0x8
  > 0x800'0064: 0x9000         STR       R0, [SP]
  >  int *originalA = ptrA;
  > 0x800'0066: 0x9c01         LDR       R4, [SP, #0x4]
  >  int *originalB = ptrB;
  > 0x800'0068: 0x9d00         LDR       R5, [SP]
  >  swap_pointers((void*)&ptrA, (void*)&ptrB);
  > 0x800'006a: 0x4669         MOV       R1, SP
  > 0x800'006c: 0xa801         ADD       R0, SP, #0x4
  > 0x800'006e: 0xf7ff 0xffeb  BL        swap_pointers           ; 0x800'0048
  > ```
### 1.b What are the values in `R0` and `R1` when `swap_pointer()` is called?
  > The registers, `R0` and `R1` contain the first and second arguments and match the location of `ptrA` and `ptrB` before the call to `swap_pointer()`:
  > - **R0:** 0x20001FDC
  > - **R1:** 0x20001FD8
### 1.c Share a screenshot of the local variables inside of `main()` after the function `swap_pointer()` returns showing the values of the pointers and what they are pointing to.
  > ![Locals after `swap_pointer()` is called](problem1_locals.png)


---
## Problem 2
  > See [divAsm.s](divAsm.s) for implementation of `divAsm()`.<br>
  > See [main.c](main.c) for implementation of `problem2_main()`.
### 2.f Run your program on the board and capture a screenshot of the serial output showing the result of `divAsm`.
  > ![Serial output after `divAsm()` is called](problem2_terminal.png)


---
## Problem 3
  > See [swapCharAsm.s](swapCharAsm.s) for implementation of `swapCharAsm()`.<br>
  > See [main.c](main.c) for implementation of `problem3_main()`.
### 3.c **Bonus:** Return 0 if the two chars are identical; otherwise return 1.
  > ![Screenshot Placeholder]()


---
## Problem 4 **Bonus**
  > See [swapPointersAsm.s](swapPointersAsm.s) for implementation of `swapPointersAsm()`.<br>
  > See [main.c](main.c) for implementation of `problem4_main()`.
### 3.c Run your program on the board and capture a screenshot of the serial output showing the result of `swapPointersAsm()` subroutine.
  > ![Screenshot Placeholder]()
