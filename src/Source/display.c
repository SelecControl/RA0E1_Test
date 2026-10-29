/*
 * display.c
 *
 *  Created on: Oct 22, 2026
 *      Author: SM 031
 */


#include "display.h"
#include "hwdef.h"

#define SEG_DP_BIT      (0x80U)         /* bit7 = DP segment line */

/* Segment pattern for every scan slot (bit0 = A ... bit6 = G, bit7 = DP).
 * Slots 0..5 = digits, slot 6 = CC7 LEDs. Written by main, read by the 1 ms interrupt. */
static volatile U8 seg_buf[NUM_CC] = {0};

static U8 current_digit = 0;
static U8 active_digit  = DIGIT_NONE;

static const bsp_io_port_pin_t cc_pins[NUM_CC] = { CC1, CC2, CC3, CC4, CC5, CC6, CC7 };

static const U8 seg_lut[10] =
{
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F      /* 0..9 */
};

static void all_cc_off(void)
{
    for (U8 i = 0; i < NUM_CC; i++)
    {
        PIN_LOW(cc_pins[i]);
    }
}

static void write_bit(bsp_io_port_pin_t pin, U8 on)
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

static void set_segments(U8 pattern)
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
    for (U8 i = 0; i < NUM_CC; i++)
    {
        seg_buf[i] = 0;
    }
    all_cc_off();
    set_segments(0);
    current_digit = 0;
    active_digit  = DIGIT_NONE;
}

void display_set_number(U8 digit, U8 value)
{
    if ((digit < NUM_DIGITS) && (value < 10U))
    {
        U8 dp = seg_buf[digit] & SEG_DP_BIT;          /* remember this digit's DP */
        seg_buf[digit] = (U8) (seg_lut[value] | dp);
    }
}

void display_set_dp(U8 digit, U8 on)
{
    if (digit < NUM_DIGITS)
    {
        if (on)
        {
            seg_buf[digit] = (U8) (seg_buf[digit] | SEG_DP_BIT);
        }
        else
        {
            seg_buf[digit] = (U8) (seg_buf[digit] & (U8) ~SEG_DP_BIT);
        }
    }
}

void display_set_leds(U8 pattern)
{
    seg_buf[LED_SLOT] = pattern;
}

/* Called every 1 ms from the timer interrupt. Lights ONE slot per call. */
void display_scan(void)
{
    all_cc_off();
    set_segments(seg_buf[current_digit]);
    PIN_HIGH(cc_pins[current_digit]);
    active_digit = current_digit;

    current_digit++;
    if (current_digit >= NUM_CC)
    {
        current_digit = 0;
    }
}

U8 display_active_digit(void)
{
    return active_digit;
}

void display_blank_digit(U8 digit)
{
    if (digit < NUM_DIGITS)
    {
        seg_buf[digit] = (U8) (seg_buf[digit] & SEG_DP_BIT);     /* clear the shape, keep the DP */
    }
}
