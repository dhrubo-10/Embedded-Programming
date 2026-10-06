#include "board.h"
#include "exercises.h"

/*
 * EX-4.2 [M] — Morse Code
 *
 * Implement Morse code using the onboard PC13 LED.
 *
 * Timing:
 *   1 unit = 100 ms
 *
 * Functions:
 *   morse_dot()        — transmit a Morse dot
 *   morse_dash()       — transmit a Morse dash
 *   morse_letter_gap() — gap between letters
 *   morse_word_gap()   — gap between words
 *
 * Requirements:
 *   1. Encode and repeatedly transmit "SOS".
 *   2. Encode and transmit the name "DHRUBO".
 *   3. Print:
 *        Sending: S (...)
 *        Sending: O (---)
 *        Sending: S (...)
 *
 * Use the board abstraction:
 *   LED_ON()
 *   LED_OFF()
 *
 */
#define ON_DOT      100 // dot = 1 unit->100
#define OFF_DOT     100
#define ON_DASH     300 // dash = 3 unit->300
#define OFF_DASH    100
#define LETTER_GAP  200 // letter gap should be 200ms
#define WORD_GAP    600 // since we already have the 100ms delay, so we can do 600ms

static void morse_dot(void)
{
    LED_ON();
    HAL_Delay(ON_DOT);
    LED_OFF();
    HAL_Delay(OFF_DOT);
}

static void morse_dash(void)
{
    LED_ON();
    HAL_Delay(ON_DASH);
    LED_OFF();
    HAL_Delay(OFF_DASH);
}

static void morse_letter_gap(void)
{
    HAL_Delay(LETTER_GAP);
}

static void morse_word_gap(void)
{
    HAL_Delay(WORD_GAP);
}

void ex_4_2_run(void)
{
    /*
        For SOS.: we need ... --- ...
        so:
        // S
        morse_dot();
        morse_dot();
        morse_dot();
        morse_letter_gap();
        
        // 0
        morse_dash();
        morse_dash();
        morse_dash();
        morse_letter_gap();
        
        // S
        morse_dot();
        morse_dot();
        morse_dot();
     //    morse_letter_gap();

     for DHRUBO. -.. .... .-. ..- -... ---
    */

    // D
    morse_dash();
    morse_dot();
    morse_dot();
    morse_letter_gap();

    // H
    morse_dot();
    morse_dot();
    morse_dot();
    morse_dot();
    morse_letter_gap();
    
    // R
    morse_dot();
    morse_dash();
    morse_dot();
    morse_letter_gap();
    
    /**u */
    morse_dot();
    morse_dot();
    morse_dash();
    morse_letter_gap();

    // B
    morse_dash();
    morse_dot();
    morse_dot();
    morse_dot();
    morse_letter_gap();
    
    // O
    morse_dash();
    morse_dash();
    morse_dash();
}