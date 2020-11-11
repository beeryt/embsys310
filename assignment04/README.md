# EMBSYS 310 - Assignment 04

## Problems
### Problem 1
>For implementation:
>
>See [blink.c](blink.c)

#### 1.a What instructions does to the compiler produce in assembly for "writing to the GPIO bit when using bit-band alias?

>Here is my answer

#### 1.b What were the instructions produced when writing to the RCC register without using bit-banding?

>Here is my answer

### Problem 2
>For implementation:
>
>See [func.c](func.c).

#### 2.a How does the *calling* function `func2` pass the values to the *called* function `func1`?

>Here is my answer

#### 2.b What extra code did the compiler generate before calling the function `func1` with the multiple arguments?

>Here is my answer

#### 2.c What extra code did the compiler generate inside the *called* function `func1` with the multiple list of arguments?

>Here is my answer

#### 2.d Any other observations?

>Here is my answer

### Problem 3
>For implementation:
>
>See [stack.h](stack.h) for stack API<br>
>See [stack.c](stack.c) for stack implementation and design<br>
>See [stack_test.c](stack_test.c) for test cases

> I used [Unity][link-unity] for a convenient test framework. I discovered it while playing around with [Platform IO][link-pio] which uses it as their default [unit testing][link-unit-pio] framework. I personally prefer [gtest][link-gtest], but it is a C++ library and I didn't want to mix C/C++ for this assignment.

> A challenge I wanted to impose on myself was supporting multiple stack instances and using an opaque struct in the API with *private* implementation in `stack.c`. Usually this approach involves a `stack_create`/`stack_delete` combo which uses `malloc` and friends. However, since this is an embedded target I chose to statically allocate a *"pool"* of structs. Interestingly my memory management for this *pool* is also implemented as a stack. I have stacks within stacks.

> Here is coverage of stack.c when running natively:
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
  Lines executed:100.0% of 31
```

### Problem 4 **(BONUS)**
> For implementation:
>
> See [endian.c](endian.c).

> Output of `endian.c` is provided through UART over USB. In the future I would like to use UART, DMA and a FIFO buffer to reduce CPU overhead.

#### 4.a Cortex M4 (little endian option)
```bash
```
#### 4.b Cortex M4 (big endian option)
```bash
```