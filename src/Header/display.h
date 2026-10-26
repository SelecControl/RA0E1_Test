/*
 * display.h
 *
 *  Created on: Oct 22, 2026
 *      Author: Rohan S.
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#define NUM_DIGITS      (6U)
#define DIGIT_NONE      (0xFFU)

uint8_t display_active_digit(void);
void display_init(void);
void display_set_number(uint8_t digit, uint8_t value);
void display_scan(void);

#endif /* DISPLAY_H_ */
