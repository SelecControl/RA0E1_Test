/*
 * tmr_opr.c
 *
 *  Created on: Oct 26, 2026
 *      Author: Rohan S.
 */

#include "tmr_opr.h"

/* Owned by the 1 ms interrupt (only the ISR writes these) */
static volatile tmr_state_t state      = TMR_IDLE;
static volatile uint32_t    elapsed_ms = 0;
static uint32_t             set_time_ms = 0;

/* Requests from the main loop: main only SETS them, the ISR only CLEARS them */
static volatile uint8_t     start_req  = 0;
static volatile uint8_t     reset_req  = 0;

void tmr_init(uint32_t set_ms)
{
    set_time_ms = set_ms;
    state       = TMR_IDLE;
    elapsed_ms  = 0;
    start_req   = 0;
    reset_req   = 0;
}

void tmr_start(void)
{
    start_req = 1;
}

void tmr_reset(void)
{
    reset_req = 1;
}

/* Runs every 1 ms inside the timer interrupt */
void tmr_1ms(void)
{
    /* 1. Handle requests. RESET wins over START. */
    if (reset_req)
    {
        reset_req  = 0;
        start_req  = 0;
        state      = TMR_IDLE;
        elapsed_ms = 0;
    }
    else if (start_req)
    {
        start_req  = 0;
        state      = TMR_RUNNING;     /* START always restarts from zero */
        elapsed_ms = 0;
    }

    /* 2. Count while running */
    if (TMR_RUNNING == state)
    {
        elapsed_ms++;

        if (elapsed_ms >= set_time_ms)
        {
            elapsed_ms = set_time_ms;
            state      = TMR_DONE;
        }
    }
}

tmr_state_t tmr_get_state(void)
{
    return state;
}

uint32_t tmr_get_elapsed_ms(void)
{
    return elapsed_ms;
}

uint32_t tmr_get_set_ms(void)
{
    return set_time_ms;
}
