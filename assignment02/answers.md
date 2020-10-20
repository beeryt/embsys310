# EMBSYS 310 - Assignment 02


1. Inject 0x7FFFFFFF for the "counter" value in the variable window, then step through the program only once to increment "counter".
    1. What is the value of the "counter" from the "Locals" window?

    **The value of "counter" is -2147483648 after increment.**

    2. What is the value of the "counter" in the "Registers" window?

    **The "counter" variable is located at R0. The value of R0 is 0x80000000.**

    3. Please note down if the N and/or V flags are set in the APSR register and explain why.

    **N: 1 The decimal value of "counter" is negative.**<br>
    **V: 1 The "counter" value has overflowed into the sign bit.**


2. If you write all F's (0xFFFFFFFF) in the Register value for "counter" then step through the program once to increment "counter".
    1. What happens to the value of "counter" in the "Locals" window?

    **0xFFFFFFFF produces a value of -1. incrementing produces a value of 0.**

    2. Please note down if the N and/or V flags are set in the APSR register and explain why.

    **N: 0 Zero is not negative.**<br>
    **V: 0 Produces carry flag instead of overflow.**


3. Change the "counter" variable type in your code to "unsigned int". Inject the values "**0x7FFFFFFF**" then step through the program to increment the "counter" once:
    1. What is the value of "counter" in the "Locals" window after incrementing for each value?

    **The value of "counter" after incrementing is 2147483648.**

    2. Please note down if the N and/or V flags are set in the APSR register and explain why.

    **N: 1 If counter was signed this would be negative.**<br>
    **V: 1 If counter was signed there would have been an overflow.**


4. Change the "counter" variable type in your code to "unsigned". Inject the values "**0xFFFFFFFF**" then step through the program to increment the "counter" once:
    1. What is the value of "counter" in the "Locals" window after incrementing for each value?

    **The value of "counter" is 0.**

    2. Please note down if the N and/or V flags are set in the APSR register and explain why.

    **N: 0 Zero is not negative.**<br>
    **V: 0 Produces carry and zero flag instead of overflow.**


5. Move the "counter" variable outside of main (at the top of the file):
    1. What is the scope of the variable "counter"?

    **The "counter" variable is now global scope.**

    2. Is it still visible in the "Locals" view?

    **No.**

    3. In which window view can we track "counter" now?

    **Global scope variables can be found in the Statics window since they have static memory addresses (at link time).**

    4. What is the address of the "counter" variable in memory?

    **The address of "counter" is 0x20000000.**


6. Change the source code to the following, then run the program in the simulator:
    1. What is the value of "counter" at the end of the program (halting at the **return 0** statement)

    **The value of "counter" is 4.**

    2. Explain why the counter value has changed?

    **It has been incremented 4 times. Both `++(*p_int)` and `counter++` increment the same location in memory. `++(*p_int)` is a *pre-increment* of the dereferenced pointer, p_int, which points at counter.**


7. Change the setting of IAR to run the same program on the **evaluation board:**
    1. What is the address where "counter" is stored?

    **The address of "counter" is 0x20000000.**

    2. Is the "counter" variable stored in RAM or ROM?

    **It is stored in RAM at runtime.**

    3. What is the value of "counter" at the end of the program (halting at the **return 0** statement).

    **The value of "counter" is 4.**
