# EMBSYS 310 - Assignment 04

1. Follow the same steps as we did in the class to blink LED1 (PA5) at a visible rate using the bit-band region to enable the clock to Port A, then answer the following:
    1. What instructions does the compiler produce in assembly for "writing" to the GPIO bit when using bit-band address?
    2. What were the instructions produced when writing to the RCC register without using bit-banding?

    >**See [blink.c](blink.c).**



2. Create a function `func1` with 5 arguments and call `func1` from within another function `func2`. Trace through the assembler and note the following:
    1. How does the *calling* function `func2` pass the values to the *called* function `func1`?
    2. What extra code did the compiler generate before calling the funciton `func1` with multiple arguments?
    3. What extra code did the compiler generate inside the *called* function `func1` with the multiple list of arguments?
    4. Any other observations?

    >**See [func.c](func.c).**



3. Following the queue data structure approach: design, implement, and test a *stack data structure*:
    1. The following is the list of requirements
        i. The stack should have a predefined size
        ii. The stack supports `int` data types
        iii. Provide a function to initialize the stack internals
        iv. Provide a function to push an element onto the stack
        v. Provide a function to pop an element off the stack
        vi. Provide a function that returns 1 if stack is empty
        vii. Provide a function that returns 1 if stack is full
        viii. *Return an error code on function failure*
        xi. *Provide a function that returns the size of the stack*
        x. *Allow multiple instances of the stack*
    2. Provide a list of the test cases and the implementation inside of main.c
    3. Separate the stack code from the rest of the test code (stack.h & stack.c)

    >**See [stack.h](stack.h).**

    >**See [stack.c](stack.c).**

    >**See [stack_test.c](stack_test.c).**

    >I used [Unity](http://www.throwtheswitch.org/unity) for a convinient test framework. I personally prefer [gtest](https://github.com/google/googletest), but that is a C++ library.



4. *Bonus:* Using the power of pointers and type casting: create a function that can determine if a processor is big-endian or little-endian. Test your function in the simulator to try both architectures.

    >**See [endian.c](endian.c)
