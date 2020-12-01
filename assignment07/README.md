# EMBSYS 310 - Assignment 07
- [Problem 1](#problem-1)
- [Problem 2](#problem-2)
- [Problem 3](#problem-3-bonus)

## Problem 1
### 1.b Define your own vector table as we did during class
  > See [startup_stm32l475xx.c](startup_stm32l475xx.c) for implementation of `__vector_table`.
### 1.c Setup the SysTick timer to trigger an interrupt every 1ms
  > See [main.c:22](main.c#L22) for configuration of SysTick.<br>
  > See [main.c:42](main.c#L42) for implementation of SysTick_Handler.
### 1.e Implement delay() function to be accurate to the millisecond
  > See [main.c:53](main.c#L53) for implementation of delay.

![Demo GIF](demo.gif)

## Problem 2
### 2.a How much total ROM is your program occupying?
  > The total ROM my program occupies is **444 bytes**.
### 2.b How much total RAM is your program using?
  > The total RAM my program uses is **16 + 8192 bytes**.
### 2.c What part of your program is using the most ROM?
  > `main.o` is the single largest object file at 196 bytes. However, `rt7M_t1.a` has a combined size of 214 bytes. These values are not the file sizes, but the machine code sizes from the .map file.
### 2.d What part of your program is using the most RAM?
  > `main.o` is using 4 bytes for the global `g_milliseconds_elapsed`, but IAR by default allocates 8192 (0x2000) bytes for the CSTACK.

```
*******************************************************************************
*** MODULE SUMMARY
***

    Module                 ro code  ro data  rw data
    ------                 -------  -------  -------
command line/config:
    ------------------------------------------------
    Total:

C:\Users\Carl\Desktop\UW_Workspace\embsys310\assignment07\iar\Debug\Obj: [1]
    main.o                     196                 4
    startup_stm32l475xx.o        2
    ------------------------------------------------
    Total:                     198                 4

dl7M_tln.a: [2]
    exit.o                       4
    low_level_init.o             4
    ------------------------------------------------
    Total:                       8

rt7M_tl.a: [3]
    cexit.o                     10
    cmain.o                     30
    cstartup_M.o                12
    data_init.o                 40
    vector_table_M.o            64
    zero_init3.o                58
    ------------------------------------------------
    Total:                     214

shb_l.a: [4]
    exit.o                      20
    ------------------------------------------------
    Total:                      20

    Gaps                         4
    Linker created                       16    8'192
----------------------------------------------------
    Grand Total:               444       16    8'196
```


## Problem 3 (bonus)
### Is there anything that can be done to optimize the usage of ROM or RAM resources?
  > Reducing the CSTACK limit is the single largest optimization for RAM resources. For instance, this program uses barely any stack. A CSTACK limit of 0x64 is plenty and reduces the total RAM usage to 116 bytes. Keep in mind reducing the stack may leave you more prone to stack corruption and esoteric bugs.
  >
  > Optimizing for ROM is mainly done through the compiler optimization flags. Specifically `-Os` is defined to optimize for size, but there is a speed trade-off.