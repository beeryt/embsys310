# Review Module 02
- IDE: IAR, debug views, host, target, cross compiling, and tool chains
- Evaluation board: STM32 Discovery Kit (IoT Node)
- C Programming: Preprocessor, variables, operators, flow control
- Cortex M4 CPU registers - How many? What is the PC register?
- Variables & Pointers

# Module 03

## Blinking the LED
### Documentation
Add Cortex M4 Generic User Guide ([DUI0553](https://documentation-service.arm.com/static/5f2ac76d60a93e65927bbdc5)) to website.
### Tracing our LED
### Group Demo
### Memory Map
### Configuring the GPIO
```C
// RCC_AHB2ENR: Enable clock for GPIOB
*((unsigned int*)0x4002104C) = 0x02;
// GPIOB_MODER: Set PB14 to output
*((unsigned int*)0x48000400) = 0xDFFFFEBF;
// GPIOB_ODR: Turn on LED2 (PB14)
*((unsigned int*)0x48000414) |= 1<<14;
```
### Blinking LED in C Code

## C Programming (continued)
### Preprocessor
### Volatile
### Bitwise operators in C

## STM32CubeMX
### Generating code for eval board
### Demo
