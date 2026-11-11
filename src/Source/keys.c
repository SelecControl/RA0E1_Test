/*
 * keys.c
 *
 *  Created on: Nov 6, 2026
 *      Author: SM 031
 */
#include "keys.h"
#include "hwdef.h"
#include "display.h"

#define KEY_DEBOUNCE_COUNT (3U)
#define LONG_PRESS_TIME (3000U)
#define NUM_KEYS (3U)

static volatile U8 key_bits = 0U;
static U8 last_bits = 0U;
static U8 same_count = 0U;
static volatile U8 key_state = 0U;
static U8 long_done = 0U;

static U16 hold_time = 0U;
static U8 pressed_keys = 0U;

static volatile U8 key_event = 0U;

/*
 * Called from the 1 ms interrupt to sample the key state. The key is connected to the CCx line of the active digit.
 * */
void key_sample(void)
{
    U8 active_cc = display_active_digit();
    if(key_state != 0U)
    {
        if(long_done == 0U)
        {
            hold_time++;
            if(hold_time >= LONG_PRESS_TIME)
            {
                key_event = KEY_EVT_LONG;
                long_done = 1U;
            }
        }
    }
    if(active_cc >= NUM_KEYS)
    {
        return;
    }
    bsp_io_level_t kbd_level = BSP_IO_LEVEL_HIGH;
    R_IOPORT_PinRead(&g_ioport_ctrl, KBD_RET, &kbd_level);
    if(kbd_level == BSP_IO_LEVEL_LOW)
    {
        key_bits |= (1U << active_cc);
    }
    else
    {
        key_bits &= (U8)~(1U << active_cc);
    }
    if(active_cc == 2U)
    {
        if(key_bits == last_bits)
        {
            if(same_count < KEY_DEBOUNCE_COUNT)
            {
                same_count++;
            }
        }
        else
        {
            last_bits = key_bits;
            same_count = 0U;
        }
        if(same_count >= KEY_DEBOUNCE_COUNT)
        {
            /* PRESS: old (key_state) == 0, new (last_bits) != 0 */
            if((last_bits != 0U) && (key_state == 0U))
            {
                pressed_keys = last_bits;
                hold_time = 0U;
                long_done = 0U;

            }
            /* RELEASE: old (key_state) != 0, new (last_bits) == 0 */
            if((last_bits == 0U) && (key_state != 0U))
            {
                if(long_done == 0U)
                {
                    key_event = KEY_EVT_SHORT;
                }
            }
            key_state = last_bits;
        }
    }

}

U8 key_get_pressed(void)
{
    return pressed_keys;
}

U8 key_get_event(void)
{
    U8 sent_key_event;

    FSP_CRITICAL_SECTION_DEFINE;            /* a place to save the interrupt state */
    FSP_CRITICAL_SECTION_ENTER;             /* interrupts held off from here ...   */
    sent_key_event = key_event;
    key_event = 0U;
    FSP_CRITICAL_SECTION_EXIT;              /* ... to here, then restored          */

    return sent_key_event;
}
