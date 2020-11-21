# EMBSYS 310 - Assignment 05
- [Problem 1](#Problem-1)
- [Problem 2](#Problem-2)
- [Problem 3](#Problem-3)
- [Problem 4](#Problem-4)


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
  > Assembly Placeholder
  > ```
### 1.b What are the values in `R0` & `R1` when `swap_pointer()` is called?
  > Answer Placeholder
### 1.c Share a screenshot of the local variables inside of `main()` after the function `swap_pointer()` returns showing the values of the pointers and what they are pointing to.
  > ![Screenshot Placeholder]()


---
## Problem 2
  > See [divAsm.s](divAsm.s) for implementation of `divAsm()`.<br>
  > See [main.c](main.c) for implementation of `problem2_main()`.
### 2.f Run your program on the board and capture a screenshot of the serial output showing the result of `divAsm`.
  > ![Screenshot Placeholder]()


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