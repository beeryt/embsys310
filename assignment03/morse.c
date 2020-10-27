/*
 *  File:       morse.c
 *  Author:     Carl B. Smiley
 *  Date:       Oct 26 2020
 *  Course:     Fundamentals of Embedded and Real Time Systems
 *
 * Description: displays my name using morse code on LED1
 */
#include <ctype.h> // toupper
#include <string.h> // strlen

// Base addresses for peripherals from Table 19 in DS10969 Rev 5
#define RCC_AHB2ENR_BASE        0x40021000
#define GPIOA_BASE              0x48000000

// Macros for convinient register access
#define RCC_AHB2ENR             (*((unsigned*)(RCC_AHB2ENR_BASE + 0x4C)))
#define GPIOA_MODER             (*((unsigned*)(GPIOA_BASE       + 0x00)))
#define GPIOA_ODR               (*((unsigned*)(GPIOA_BASE       + 0x14)))

// Macros for bit values
#define GPIOAEN                 (1<<0)
#define MODE5_0                 (1<<10)
#define MODE5_1                 (1<<11)
#define OD5                     (1<<5)

// TODO remove since LED2 is not used
#define GPIOB_BASE 0x48000400
#define GPIOB_MODER (*((unsigned*)(GPIOB_BASE+0x00)))
#define GPIOB_ODR (*((unsigned*)(GPIOB_BASE+0x14)))
#define GPIOBEN (1<<1)
#define MODE14_1 (1<<29)
#define OD14 (1<<14)

// Morse code timing constants
#define MORSE_DELAY_DIT      100000             /* '.' base unit of time */
#define MORSE_DELAY_DAH (3 * MORSE_DELAY_DIT)   /* '-'                   */
#define MORSE_DELAY_GAP      MORSE_DELAY_DIT    /* signal absence period */
#define MORSE_DELAY_EOL (3 * MORSE_DELAY_DIT)   /* end of letter delay   */
#define MORSE_DELAY_EOW (7 * MORSE_DELAY_DIT)   /* end of word delay     */

// Lookup table for morse sequences
char* morse_lut[] = {
  /*A*/ ".-",    /*B*/ "-...",  /*C*/ "-.-.",  /*D*/ "-..",
  /*E*/ ".",     /*F*/ "..-.",  /*G*/ "--.",   /*H*/ "....",
  /*I*/ "..",    /*J*/ ".---",  /*K*/ "-.-",   /*L*/ ".-..",
  /*M*/ "--",    /*N*/ "-.",    /*O*/ "---",   /*P*/ ".--.",
  /*Q*/ "--.-",  /*R*/ ".-.",   /*S*/ "...",   /*T*/ "-",
  /*U*/ "..-",   /*V*/ "...-",  /*W*/ ".--",   /*X*/ "-..-",
  /*Y*/ "-.--",  /*Z*/ "--..",  /*0*/ "-----", /*1*/ ".----",
  /*2*/ "..---", /*3*/ "...--", /*4*/ "....-", /*5*/ ".....",
  /*6*/ "-....", /*7*/ "--...", /*8*/ "---..", /*9*/ "----.",
};
const int morse_max_lut_idx = 36;


/** Converts char to lookup index or -1 on error */
int morse_lut_lookup(char c) {
  c = toupper(c);
  if (c >= 'A' && c <= 'Z')     return (c - 'A');
  if (c >= '0' && c <= '9')     return (c - '0') + 26;
  return -1;
}

/** Basic busy wait */
void wait(unsigned cycles) {
  while (--cycles > 0);
}

/** Converts string to morse sequence and displays on LED1 */
void morse_print(const char* str) {
  // process each letter in string
  for (int i = 0; i < strlen(str); ++i) {
    if (str[i] == ' ') wait(MORSE_DELAY_EOW);   // end-of-word delay on space

    unsigned idx = morse_lut_lookup(str[i]);         // convert to morse sequence
    if (idx > morse_max_lut_idx) continue;      // skip undefined sequences
    const char* morse = morse_lut[idx];
    const int len = strlen(morse);
    for (int j = 0; j < len; ++j) {
      GPIOA_ODR |= OD5;                         // turn LED1 on
      switch (morse[j]) {                       // wait based on symbol type
        case '.': wait(MORSE_DELAY_DIT); break;
        case '-': wait(MORSE_DELAY_DAH); break;
        default: break;
      }
      GPIOA_ODR &= ~OD5;                         // turn LED1 off
      if (j < len - 1) wait(MORSE_DELAY_GAP);   // signal absence period
    }

    wait(MORSE_DELAY_EOL);                      // end-of-letter delay
  }
}

int main() {
  // set up LED1 (PA5) as a GPIO output
  RCC_AHB2ENR |=  GPIOAEN;      // enable GPIOA clock
  GPIOA_MODER &= ~MODE5_1;      // enable output for PA5 from reset state

  // display my name in morse indefinitely
  while(1) {
    morse_print("Carl B. Smiley");
  }
}