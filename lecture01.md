# Introduction
Tamer Awad
  - UW Graduate EE
  - Worked on motherboards enterprise servers at Intel ~5yr
  - PLD programming in VHDL
  - Chipset validation, PCIexpress logic
  - Moved to Microsoft after 10yr at Intel, (10yr at Microsoft)
  - Worked on Ford Sync automotive, switched to IoT (small company within company in Microsoft)
  - Based in Seattle WA area. Took this course 3 years ago. Second year instructing this course.
Gideon Lee
  - Teaching Assistant for all three courses this year
  - Software background, took this course 7-8yr ago

# Embedded & Realtime Systems Programming Certificate
Three course overview:


## EMBSYS 100
- Intro to computer arch and hardware concepts
- Number System and algebra
- C programming
- Intro to ARM
- Embedded development tools and evaluation kit


## EMBSYS 105:
- RTOS and how to port to uC
- programming multitasking system
- driver frameworks
- display, audio, and touch screen modules


## EMBSYS 110:
- C++ for embedded systems
- Hierarchical State Machines (HSM) and event driven design
- State chart design, patterns, and framework
- Use of connectivity and sensor modules

# About The Class
## Grading and Attendance
This is a *pass/fail* course.
Participate for *at least 60% fo the sessions*.
Complete a minimum of 80% of total assignments.
A non-graded quiz to track attendance and cover topics in lecture.
This course does not have projects, but subsequent courses will.

## Course Materials and technologies
Two books are highly recommended. Primarily *The Definitive Guide to ARM Cortex-M3 and Cortex-M4 Processors.*


## Class Format
- lectures
- demos
- discussions
- quizzes
- breaks


# Course Outline
1. Introduction to Embedded Systems
2. Embedded development environment
3. C Programming Language
4. Embedded evaluation board
5. Assembly language
6. Introduction to ARM architecture
7. Exceptions, interrupts, and interrupt handling
8. Embedded software architectures
9. Intro to Realtime Operating System (RTOS) and its services


# Module 01
1. Introduciton to embedded systems
2. Basic hardware architecture
3. Number Systems
4. Basic computer math, arithmetic and logic
5. Software version control using Git
6. Assignment 01


## 01.1 Introduction to embedded systems
> An [**embedded system**](https://en.wikipedia.org/wiki/Embedded_system) is a dedicated computer system designed for a specific functionality.

> It is **embedded** as part of a product that includes hardware, electrical, and mechanical components

Roughly 98% of all microprocessors manufactured are used in embedded systems.

### Examples of Embedded Systems
- Digital watches
- Traffic light controllers
- Components in vehicles (CAN bus)
- Medical equipment
- Avionic systems
- PLCs
- IoT devices


### Embedded Systems VS General Purpose Computers
| Embedded Systems | General Purpose |
| - | - |
| Single Function | Multipe FUnction |
| RTOS | relaxed timing |
| limited resources | larger hardware resources |
| no human interaction | human accessible |

### Telegraph Example
In *Embedded System Primer* they talk about the Telegraph Example.

#### Development Challenges
- Troughput:  handling a lot of data in short time
- Response:   React quickly
- Testability
- Debugability: no screen. no keyboard
- Reliability:  no human intervention once deployed
- Memory:       limited memory
- Program installation: Special tools ot install and upgrade firmware
- Power consumption:  battery power needs to conserve power
- Security: Who can access this device?
- Cost: Reducing cost is high priority (from business perspective)
> Expect that your software operates on hardware that is barely adequate for the job

### So why do it?
- The challenges are very rewarding
- Directly working with **hardware**
- Deep understanding of computer
- The global market is **growing** at a rapid pace with revolution of **IoT**

### Assignment 1.a
> Using the telegraph example, and the challenges listed in the book, describe another device that you would like to discuss. Describe how you think its embedded system works, and what design challenges it presents.


## 01.2 Basic Architecture
### Microcontroller vs. Microprocessor
From *The Definitive Guide to ARM Cortex M3 & M4* a microcontroller is a microprocessor with memory and peripherals.

### A Typical Embedded Hardware System
- CPU
- Memory
- Input/Output
Comunicate over different busses (address bus, data buss, control bus)

#### Memory
*What is memory for?*
Stores *data*, Stores *instructions*
##### Memory Types
RAM vs ROM
##### Memory Types - RAM
Random Access Memory (RAM)
- code and data are stored in RAM
- volatile memory is lost when power is lost

##### Memory Types - ROM
Read Only Memory (ROM)
- Stores information essential to OS, like bootloader
- not volatile
- Used when data doesn't need to change
- Different flavors
  - PROM (Programmable read only memory)
  - EPROM (Erasable Programmable Read only memory)
  - EEPROM (Electrically erasable Programmable Read Only Memory)

##### Memory Types - Flash
- A form of EEPROM
- Faster than EEPROM
- Larger in size
- stores the program code


##### Memory Table
Memory table is a 2D Matrix
- Table width is the number of data lines (8,16,32-bit)
- Address provides table index
- Size depends on number of address lines

##### Bus
- Address lines   microprocessor to memory chips
- Data Lines      same as address
- Read line       output enable signal
- Write line      input enable signal
Communication is determined by a *Protocol*, or set of rules for exchanging data (SPI, I2C, AMBA, etc)

##### Clock
- Provides rising/falling edge to the circuit
- Generated with oscillators or crystals


##### Hardware Registers
- used extensively in computer architecture
- primary interface between HW and SW


##### Peripherals
- Hardware devices which reside outside of the processor (could be within the microcontroller)
- Communicate via interrupts, I/O, or memory-mapped registers


## 01.3 Number Systems
- Bit, Byte, Nibble, Word, Double Word
- Decimal, Binary, Octal, Hexadecimal
- Binary to Hex 10101011 -> 1010 1011 -> 0xAB
- Binary arithmetic
- Machine "word" is determined by the processor. Commonly 8,16,24,32 or 64-bit
- Byte ordering: big-endian vs little-endian
- Unsigned vs Signed integers
- Two's Complement
- Overflow

## 01.4 Basic computer logic
- Boolean Algebra & Logical Operators
- Bitwise operations
- Truth Table

### Boolean Algebra
- Historically relevant since 1854
- Used to analyze and simplify digital (logic) circuits
- de Morgan's Theroem (A||B) -> (!A)&&(!B)
- Logical Operations (! && ||) NOT, AND, OR
- Bitwise Operations (~ & | ^) NOT, AND, OR, XOR
- Shift operators << >>


## 01.5 Software Version Control
- Git
- Basic Git Flow
- Setting Up Repos

## 01.6 Assignment 01
Create new repo [https://github.com/<yourname>/embsys310](https://github.com/beeryt/embsys310)
