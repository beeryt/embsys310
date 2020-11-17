# Module 06

## Embedded Software Architecture
### Round Robin
### Round Robin w/ Interrupt
#### Shared data problem
```C
static iTemperatures[2];
void interrupt vReadTemperatures(void) {
  iTemperatures[0] = // read input value from hardware
  iTemperatures[1] = // read input value form hardware
}
void main(void) {
  int iTemp0, iTemp1;
  while (1) {
    iTemp0 = iTemperatures[0];
    iTemp1 = iTemperatures[1];
    if (iTemp0 != iTempm1) { // trigger alarm }
  }
}
```
**Solution:** disable interrupts
### Funciton-queue-scheduling architecture
### Real-Time Operating System Architecture


## C Programming -- Functions (continued)
#### Arm Architecture Procedure Call Standard (AAPCS)
| Register | Function Call Behavior |
|-|-|
|R0-R3, R12|Caller Saved Registers|
|R4-R11|Callee Saved Registers|
|R14(LR)|Link Register should be saved to stack if function is not a "leaf"|
|R13(SP, R15(PC)|Should not be used for normal processing|
#### Recursion
## Pitfalls with functions
## Pitfalls with arguments & pointers
## Assembly Programming
