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

static volatile U8 key_bits = 0U;
static U8 last_bits = 0U;
static U8 same_count = 0U;
static volatile U8 key_state = 0U;
static volatile U16 key_changed = 0U;

/*
 * Called from the 1 ms interrupt to sample the key state. The key is connected to the CCx line of the active digit.
 * */
void key_sample(void)
{
    U8 active_cc = display_active_digit();
    if(active_cc >> 3U)
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
        key_bits &= ~(1U << active_cc);
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
            key_state = last_bits;
            key_changed++;
        }
    }
}

U8 key_get_bits(void)
{
    return key_state;
}
