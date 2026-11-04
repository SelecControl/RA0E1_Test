/*
 * din.c
 *
 *  Created on: Oct 23, 2026
 *      Author: SM 031
 */


#include "din.h"
#include "hwdef.h"

#define RESET_DEBOUNCE_MS   (20U)       /* RESET must be stable this long before we accept it */
#define START_DEBOUNCE_MS   (20U)       /* START level must be stable this long */

static volatile U16 start_count    = 0;    /* written ONLY by the START interrupt  */
static volatile U8  reset_active   = 0;    /* written ONLY by the 1 ms interrupt   */
static U8           reset_last_raw = 0;
static U8           reset_same_ms  = 0;

static volatile U8  start_active   = 0;    /* written ONLY by the 1 ms interrupt   */
static U8           start_last_raw = 0;
static U8           start_same_ms  = 0;

void din_init(void)
{
    start_count    = 0;
    reset_active   = 0;
    reset_last_raw = 0;
    reset_same_ms  = 0;
    start_active   = 0;
    start_last_raw = 0;
    start_same_ms  = 0;
}

/* ---------------- RESET: polled every 1 ms, debounced ---------------- */
void din_1ms(void)
{
    bsp_io_level_t level = BSP_IO_LEVEL_HIGH;
    R_IOPORT_PinRead(&g_ioport_ctrl, DI_RESET, &level);

    U8 raw = (BSP_IO_LEVEL_LOW == level) ? 1U : 0U;    /* LOW = terminal shorted = active */

    if (raw == reset_last_raw)
    {
        if (reset_same_ms < RESET_DEBOUNCE_MS)
        {
            reset_same_ms++;
        }
    }
    else
    {
        reset_last_raw = raw;
        reset_same_ms  = 0;
    }

    if (reset_same_ms >= RESET_DEBOUNCE_MS)
    {
        reset_active = raw;
    }

    /* ---------------- START level: same debounce as RESET ---------------- */
    bsp_io_level_t s_level = BSP_IO_LEVEL_HIGH;
    R_IOPORT_PinRead(&g_ioport_ctrl, DI_START, &s_level);

    U8 s_raw = (BSP_IO_LEVEL_LOW == s_level) ? 1U : 0U;    /* LOW = terminal shorted = active */

    if (s_raw == start_last_raw)
    {
        if (start_same_ms < START_DEBOUNCE_MS)
        {
            start_same_ms++;
        }
    }
    else
    {
        start_last_raw = s_raw;
        start_same_ms  = 0;
    }

    if (start_same_ms >= START_DEBOUNCE_MS)
    {
        start_active = s_raw;
    }
}

/* ---------------- START: one call per falling edge (interrupt) ---------------- */
void din_start_edge(void)
{
    start_count++;
}

U16 din_get_start_count(void)
{
    return start_count;
}

U8 din_reset_active(void)
{
    return reset_active;
}

U8 din_start_active(void)
{
    return start_active;
}
