/*
 * tick.c
 *
 *  Created on: Oct 29, 2026
 *      Author: Rohan S.
 */

/* tick.c */
#include "tick.h"

static volatile U32 ms_count = 0;       /* written ONLY by the 1 ms interrupt */

void tick_1ms(void)
{
    ms_count++;
}

U32 tick_get_ms(void)
{
    return ms_count;
}
