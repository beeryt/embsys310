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
        1. The stack should have a predefined size
        2. The stack supports `int` data types
        3. Provide a function to initialize the stack internals
        4. Provide a function to push an element onto the stack
        5. Provide a function to pop an element off the stack
        6. Provide a function that returns 1 if stack is empty
        7. Provide a function that returns 1 if stack is full
        8. **Return an error code on function failure**
        9. **Provide a function that returns the size of the stack**
        10. **Allow multiple instances of the stack**
    2. Provide a list of the test cases and the implementation inside of main.c
    3. Separate the stack code from the rest of the test code (stack.h & stack.c)


    >**See [stack.h](stack.h) for stack API.**
    >
    >**See [stack.c](stack.c) for stack implementation and design.**
    >
    >**See [stack_test.c](stack_test.c) for test cases.**

    >I used [Unity](http://www.throwtheswitch.org/unity) for a convenient test framework.
    >I discovered it while playing around with [Platform IO](https://docs.platformio.org/en/latest/home/index.html) which uses it as their default [unit testing](https://docs.platformio.org/en/latest/tutorials/core/unit_testing_blink.html#tutorial-unit-testing-blink) framework.
    >I personally prefer [gtest](https://github.com/google/googletest#googletest), but that is a C++ library.

    >A challenge I wanted to impose on myself was using an opaque struct in the API with *private* implementation in [stack.c](stack.c).
    >Usually this approach involves a `stack_create`/`stack_delete` combo which uses `malloc` and friends.
    >However, since this is an embedded target I chose to statically allocate a *"pool"* of structs.
    >Interestingly my memory management for this pool is implemented as a stack. Stacks within Stacks.

    >Here is the coverage of [stack.c](stack.c) when running natively:
    ```bash
    $ gcc --coverage -I. -Iexternal/Unity/src external/Unity/src/unity.c stack.c stack_test.c -o stack
    $ ./stack
      stack_test.c:313:test_stack_create_should_be_valid:PASS
      stack_test.c:314:test_stack_create_should_be_empty:PASS
      stack_test.c:315:test_stack_delete_invalidates_handle:PASS
      stack_test.c:316:test_stack_create_all_stack_pool:PASS
      stack_test.c:318:test_stack_push_error_on_invalid_handle:PASS
      stack_test.c:319:test_stack_pop_error_on_invalid_handle:PASS
      stack_test.c:320:test_stack_full_error_on_invalid_handle:PASS
      stack_test.c:321:test_stack_empty_error_on_invalid_handle:PASS
      stack_test.c:322:test_stack_size_error_on_invalid_handle:PASS
      stack_test.c:324:test_pop_from_empty_stack:PASS
      stack_test.c:325:test_push_to_full_stack:PASS
      stack_test.c:326:test_push_until_full:PASS
      stack_test.c:327:test_pop_until_empty:PASS
      stack_test.c:328:test_push_then_pop_single_item:PASS
      stack_test.c:329:test_push_then_pop_all_items:PASS
      stack_test.c:330:test_push_then_pop_all_items_interleaved:PASS

      -----------------------
      16 Tests 0 Failures 0 Ignored
    $ gcov stack.c
      File 'stack.c'
      Lines executed:100.00% of 31
    ```



4. **Bonus:** Using the power of pointers and type casting: create a function that can determine if a processor is big-endian or little-endian. Test your function in the simulator to try both architectures.

    >**See [endian.c](endian.c).**
