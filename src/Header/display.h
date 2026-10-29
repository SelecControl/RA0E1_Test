/*
 * display.h
 *
 *  Created on: Oct 22, 2026
 *      Author: Rohan S.
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "typedef.h"

#define NUM_DIGITS      (6U)            /* numeric digits: CC1..CC6                */
#define NUM_CC          (7U)            /* scan slots: 6 digits + LED slot (CC7)   */
#define LED_SLOT        (6U)            /* index of CC7 in the scan                */
#define DIGIT_NONE      (0xFFU)

void display_init(void);
void display_set_number(U8 digit, U8 value);   /* 0..9 on digit 0..5, keeps its DP */
void display_set_dp(U8 digit, U8 on);          /* decimal point of digit 0..5      */
void display_set_leds(U8 pattern);             /* CC7 LEDs, bit n = segment line n */
void display_scan(void);
U8   display_active_digit(void);
void display_blank_digit(U8 digit);

#endif /* DISPLAY_H_ */
