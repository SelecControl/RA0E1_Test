/*
 * display.h
 *
 *  Created on: Oct 22, 2026
 *      Author: Rohan S.
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "typedef.h"

#define NUM_DIGITS      (6U)
#define DIGIT_NONE      (0xFFU)

U8 display_active_digit(void);
void display_init(void);
void display_set_number(U8 digit, U8 value);
void display_scan(void);

#endif /* DISPLAY_H_ */
