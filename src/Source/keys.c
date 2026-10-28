/*
 * keys.c
 *
 *  Created on: Oct 23, 2026
 *      Author: SM 031
 */

#include "keys.h"
#include "display.h"
#include "hwdef.h"

///* A new key pattern must be seen this many scan cycles in a row before we accept it.
// * One scan cycle = 6 digits x 1 ms = 6 ms, so 4 cycles = 24 ms debounce. */
//#define KEY_DEBOUNCE_CYCLES     (4U)

#define KEY_DEBOUNCE_MS         (20U)          /* required debounce time            */
#define KEY_SCAN_PERIOD_MS      (NUM_DIGITS)   /* one full CC cycle, 1 ms per CC    */

/* Cycles needed, rounded UP so we never debounce for less than KEY_DEBOUNCE_MS */
#define KEY_DEBOUNCE_CYCLES     ((KEY_DEBOUNCE_MS + KEY_SCAN_PERIOD_MS - 1U) / KEY_SCAN_PERIOD_MS)

#define KEY_LONG_PRESS_MS       (3000U)     /* XT546: "press for 3 sec" */

static U8          cycle_bits  = 0;    /* keys seen pressed in the current 6 ms cycle   */
static U8          last_bits   = 0;    /* pattern from the previous cycle               */
static U8          same_count  = 0;    /* how many cycles in a row last_bits repeated   */
static volatile U8 key_state   = 0;    /* debounced result, read by the main loop       */

/* ---- event detection ---- */
static U8              held_bits    = 0;   /* key pattern currently being timed          */
static U16             held_ms      = 0;   /* how long held_bits has been held           */
static U8              used_bits    = 0;   /* every key touched since all keys were free */
static U8              long_done    = 0;   /* 1 = long event already sent for this press */
static volatile key_event_t pending_evt  = KEY_EVT_NONE;   /* one-slot mailbox to main loop */

static void post_event(key_event_t evt)
{
    if ((KEY_EVT_NONE != evt) && (KEY_EVT_NONE == pending_evt))
    {
        pending_evt = evt;
    }
}

static U8 is_single_key(U8 bits)
{
    return (U8) ((bits != 0U) && ((bits & (bits - 1U)) == 0U));
}

static key_event_t short_event(U8 bits)
{
    switch (bits)
    {
        case KEY_SET:  return KEY_EVT_SET_SHORT;
        case KEY_DOWN: return KEY_EVT_DOWN_SHORT;
        case KEY_UP:   return KEY_EVT_UP_SHORT;
        default:       return KEY_EVT_NONE;
    }
}

static key_event_t long_event(U8 bits)
{
    switch (bits)
    {
        case KEY_SET:              return KEY_EVT_SET_LONG;
        case KEY_DOWN:             return KEY_EVT_DOWN_LONG;
        case KEY_UP:               return KEY_EVT_UP_LONG;
        case (KEY_UP | KEY_DOWN):  return KEY_EVT_UP_DOWN_LONG;
        default:                   return KEY_EVT_NONE;
    }
}

/* Called once per scan cycle (every KEY_SCAN_PERIOD_MS) with the debounced key pattern */
static void key_update_events(U8 state)
{
    if (0U != state)                                    /* at least one key is held */
    {
        if (state != held_bits)                         /* new key pattern: restart the timing */
        {
            held_bits = state;
            held_ms   = 0;
        }

        used_bits |= state;

        if (held_ms < KEY_LONG_PRESS_MS)
        {
            held_ms = (U16) (held_ms + KEY_SCAN_PERIOD_MS);
        }

        if ((0U == long_done) && (held_ms >= KEY_LONG_PRESS_MS))
        {
            long_done = 1U;                             /* fire once, while still held */
            post_event(long_event(held_bits));
        }
    }
    else                                                /* all keys released */
    {
        if ((0U == long_done) && is_single_key(used_bits))
        {
            post_event(short_event(used_bits));         /* short = released before 3 s */
        }

        held_bits = 0;
        held_ms   = 0;
        used_bits = 0;
        long_done = 0;
    }
}

void key_init(void)
{
    cycle_bits = 0;
    last_bits  = 0;
    same_count = 0;
    key_state  = 0;
    held_bits   = 0;
    held_ms     = 0;
    used_bits   = 0;
    long_done   = 0;
    pending_evt = KEY_EVT_NONE;
}

/* cc_index = the digit/CC line that has been ON for the last 1 ms */
void key_sample(U8 cc_index)
{
    /* 1. Only CC1..CC3 have keys. Read KBD while that CC is still ON. */
    if (cc_index < NUM_KEYS)
    {
        bsp_io_level_t level = BSP_IO_LEVEL_HIGH;
        R_IOPORT_PinRead(&g_ioport_ctrl, KBD_RET, &level);

        if (BSP_IO_LEVEL_LOW == level)                   /* LOW = key on this CC pressed */
        {
            cycle_bits |= (U8) (1U << cc_index);
        }
    }

    /* 2. After the last key's CC has been read, the cycle is complete: debounce it. */
    if (cc_index == (NUM_KEYS - 1U))
    {
        if (cycle_bits == last_bits)
        {
            if (same_count < KEY_DEBOUNCE_CYCLES)
            {
                same_count++;
            }
        }
        else
        {
            last_bits  = cycle_bits;                     /* changed: start counting again */
            same_count = 0;
        }

        if (same_count >= KEY_DEBOUNCE_CYCLES)
        {
            key_state = last_bits;                       /* stable long enough: accept it */
        }

        cycle_bits = 0;                                  /* start collecting next cycle */
        key_update_events(key_state);

    }
}

U8 key_get_state(void)
{
    return key_state;
}

key_event_t key_get_event(void)
{
    key_event_t evt = pending_evt;

    if (KEY_EVT_NONE != evt)
    {
        pending_evt = KEY_EVT_NONE;
    }

    return evt;
}

