# EMBSYS 310 - Assignment 04

## Problems
### Problem 1
>For implementation:
>
>See [blink.c](blink.c)

#### 1.a What instructions does the compiler produce in assembly for "writing to the ~~GPIO~~ GPIOAEN bit when using bit-band alias?

>The assembly puts 1 in `R0`, loads the address of the bit-band alias, `0x4242980` into `R1`, then stores `R0` into the memory referenced by `R1`.
```asm
  PERIPHERAL_BIT_BAND(RCC_AHB2ENR_ADDR, GPIOAEN_BIT) = 1;
MOVS    R0, #1
LDR.N   R1, [PC, $0x40] ; 0x42420980
STR     R0, [R1]
```

#### 1.b What were the instructions produced when writing to the GPIOx_ODR register without using bit-banding?

>The assembly loads the GPIOA_ODR address, `0x48000014`, into `R0`. Then loads the value at that address into `R1`. An exclusive or operation is performed on bit 5 (`0x20`) and the resulting `R1` is stored into the memory referenced by `R0`.
```asm
  GPIOA_ODR ^= OD5;
LDR.N   R0, [PC, #0x20] ; 0x48000014
LDR     R1, [R0]
EORS.W  R1, R1, #32     ; 0x20
STR     R1, [R0]
```


### Problem 2
>For implementation:
>
>See [func.c](func.c).

```asm
func1:
  BX      LR
void func2() {
func2:
  PUSH    {R7, LR}
  func1(1,2,3,4,5);
  MOVS    R0, #5
  STR     R0, [SP]
  MOVS    R3, #4
  MOVS    R2, #3
  MOVS    R1, #2
  MOVS    R0  #1
  BL      func1
}
  POP     {R0, PC}
int main() {
main:
  PUSH    {R7, LR}
  func2();
  BL      func2
}
  MOVES   R0, #0
  POP     {R1, PC}
```

#### 2.a How does the *calling* function `func2` pass the values to the *called* function `func1`?

>Inside the dissasembly of `func2` the fifth argument (`#5`) is placed onto the stack (without decrementing SP?). The first four arguments are placed in `R0-R3`. A `BL` instruction branches to the `func1` label.
```asm
MOVS    R0, #5
STR     R0, [SP]
MOVS    R3, #4
MOVS    R2, #3
MOVS    R1, #2
MOVS    R0  #1
BL      func1
```

#### 2.b What extra code did the compiler generate before calling the function `func1` with the multiple arguments?

>The dissasembly shows a `PUSH {R7, LR}` instruction pushes `LR` onto the stack so we can return from `func2` (`main` does this as well).
```asm
PUSH    {R7, LR}
```


#### 2.c What extra code did the compiler generate inside the *called* function `func1` with the multiple list of arguments?

>There is no *extra* code here. Just a branch back to `LR` which at this time is inside `func2` after the `BL` instruction.
```asm
BX    LR
```

#### 2.d Any other observations?

>I wanted to invesitage why the fifth argument (`#5`) didn't decrement `SP` inside `func2`. I modified `func1` as follows:
```C
int func1(int a1, int a2, int a3, int a4, int a5) {
  return a5;
}
```
```asm
func1:
  PUSH    {R4}
  MOVS    R4, R0
  LDR     R0, [SP, #0x4]
  return a5;
  POP     {R4}
  BX      LR
```
>The new disassembly of `func1` shows a strange dance with the stack, `R4` and `R0`. I'm really not sure what the `PUSH`, `MOVS`, and `POP` instructions accomplish here. The `LDR R0, [SP, #0x4]` reads from the stack without moving `SP`. The `#0x4` is an `int` offset to avoid the `R4` which had just been pushed.

>I feel that the contents of `func1` could be written more succinctly:
```asm
func1:
  LDR   R0, [SP]
  BX    LR
```
>Most baffling is the `MOVS` instruction which appears to place the value of `a1` into `R4` before immediately overwritting it by popping into `R4`.


### Problem 3
>For implementation:
>
>See [stack.h](stack.h) for stack API<br>
>See [stack.c](stack.c) for stack implementation and design<br>
>See [stack_test.c](stack_test.c) for test cases

>To run using IAR follow these steps:
>1. Select `stack` project
>2. Configure Project Options
>    1. Select STM32L475VG
>    2. Make sure semihosting is enabled (default)
>        - General Options > Library Configuration > Semihosted
>    2. Set Debugger to Simulator (default)
>    3. Start Debugger
>    4. Open View > Terminal I/O
>    5. Press Go (F5)

> I used [Unity][link-unity] for a convenient test framework. I discovered it while playing around with [Platform IO][link-pio] which uses it as their default [unit testing][link-unit-pio] framework. I personally prefer [gtest][link-gtest], but it is a C++ library and I didn't want to mix C/C++ for this assignment.

[link-unity]: http://www.throwtheswitch.org/unity
[link-pio]: https://docs.platformio.org/en/latest/home/
[link-unit-pio]: https://docs.platformio.org/en/latest/plus/unit-testing.html
[link-gtest]: https://github.com/google/googletest

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

> Output of `endian.c` can be viewed using `View > Terminal I/O` and default project configuration for semihosting.

> I initially developed this program using PlatformIO instead of IAR which uses a different toolchain: `arm-none-eabi-gcc` with `newlib`. For that purpose I implemented `ssize_t _write(int, const void*, size_t)` but it appears IAR desires a different low-level signature for `stdio`. For now the `stdio` output is accomplished using IAR semihosting.

> Steps to see output running on device:
>1. Select `endian` project
>2. Configure Project Options
>    1. Select STM32L475VG
>    2. Make sure semihosting is enabled (default)
>        - `General Options > Library Configuration > Semihosted`
>    2. Set Debugger to Simulator (default) or ST-Link
>        - Update `ST-Link > Interface` and `ST-Link > Reset`
>    3. Start Debugger
>    4. Open `View > Terminal I/O`
>    5. Press Go (F5)


#### 4.a Cortex M4 (little endian option)
```bash
isBigEndian():      false
isLittleEndian():   true
```
#### 4.b Cortex M4 (big endian option)
```bash
isBigEndian():      true
isLittleEndian():   false
```

#### Intel x64 Processor
```bash
isBigEndian():      false
isLittleEndian():   true
```