/*
 * display.c
 *
 *  Created on: Oct 22, 2026
 *      Author: SM 031
 */


#include "display.h"
#include "hwdef.h"

/* What each digit should show (0..9). Written by main loop, read by the 1 ms interrupt. */
static volatile uint8_t display_buf[NUM_DIGITS] = {0};

/* Which digit the next display_scan() call will light. */
static uint8_t current_digit = 0;

/* Digit pins in display order: index 0 = CC1 ... index 5 = CC6 */
static const bsp_io_port_pin_t cc_pins[NUM_DIGITS] = { CC1, CC2, CC3, CC4, CC5, CC6 };

/* Segment pattern for 0..9.  bit0 = A, bit1 = B ... bit6 = G, bit7 = DP. It's a segment lookup table */
static const uint8_t seg_lut[10] =
{
    0x3F,   /* 0 : A B C D E F   */
    0x06,   /* 1 : B C           */
    0x5B,   /* 2 : A B D E G     */
    0x4F,   /* 3 : A B C D G     */
    0x66,   /* 4 : B C F G       */
    0x6D,   /* 5 : A C D F G     */
    0x7D,   /* 6 : A C D E F G   */
    0x07,   /* 7 : A B C         */
    0x7F,   /* 8 : A B C D E F G */
    0x6F    /* 9 : A B C D F G   */
};

/* Switch all digit pins off. */
static void all_cc_off(void)
{
    for (uint8_t i = 0; i < NUM_DIGITS; i++)
    {
        PIN_LOW(cc_pins[i]);
    }
}


static void write_bit(bsp_io_port_pin_t pin, uint8_t on)
{
    if (on)
    {
        PIN_HIGH(pin);
    }
    else
    {
        PIN_LOW(pin);
    }
}

static void set_segments(uint8_t pattern)
{
    write_bit(SEGA,  pattern & (1U << 0));
    write_bit(SEGB,  pattern & (1U << 1));
    write_bit(SEGC,  pattern & (1U << 2));
    write_bit(SEGD,  pattern & (1U << 3));
    write_bit(SEGE,  pattern & (1U << 4));
    write_bit(SEGF,  pattern & (1U << 5));
    write_bit(SEGG,  pattern & (1U << 6));
    write_bit(SEGDP, pattern & (1U << 7));
}

void display_init(void)
{
    all_cc_off();
    set_segments(0);
    current_digit = 0;
}

void display_set_number(uint8_t digit, uint8_t value)
{
    if ((digit < NUM_DIGITS) && (value < 10U))
    {
        display_buf[digit] = value;
    }
}

/* Called every 1 ms from the timer interrupt. Lights ONE digit per call. */
void display_scan(void)
{
    all_cc_off();                                       /* 1. switch the old digit off   */
    set_segments(seg_lut[display_buf[current_digit]]);  /* 2. load the new digit pattern */
    PIN_HIGH(cc_pins[current_digit]);                   /* 3. switch the new digit on    */

    current_digit++;
    if (current_digit >= NUM_DIGITS)
    {
        current_digit = 0;
    }
}
