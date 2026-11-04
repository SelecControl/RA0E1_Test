/*
 * tmr_opr.c
 *
 *  Created on: Oct 26, 2026
 *      Author: Rohan S.
 */

#include "tmr_opr.h"

/* Owned by the 1 ms interrupt (only the ISR writes these) */
static volatile tmr_state_t state      = TMR_IDLE;
static volatile U32    elapsed_ms = 0;
static volatile U32    set_time_ms = 0;

/* Requests from the main loop: main only SETS them, the ISR only CLEARS them */
static volatile U8     start_req  = 0;
static volatile U8     reset_req  = 0;
static volatile U8     set_req    = 0;
static volatile U32    new_set_ms = 0;

void tmr_init(U32 set_ms)
{
    set_time_ms = set_ms;
    state       = TMR_IDLE;
    elapsed_ms  = 0;
    start_req   = 0;
    reset_req   = 0;
    set_req     = 0;
    new_set_ms  = 0;
}

void tmr_start(void)
{
    start_req = 1;
}

void tmr_reset(void)
{
    reset_req = 1;
}

void tmr_set_ms(U32 set_ms)
{
    new_set_ms = set_ms;        /* value first ...            */
    set_req    = 1;             /* ... then the flag          */
}

/* Runs every 1 ms inside the timer interrupt */
void tmr_1ms(void)
{
    /* 1. Handle requests. New set value first, then RESET, then START. */
    if (set_req)
    {
        set_req     = 0;
        reset_req   = 0;
        start_req   = 0;
        set_time_ms = new_set_ms; /* timing value changed: unit resets */
        state       = TMR_IDLE;   /* new set time always resets */
        elapsed_ms  = 0;
    }
    else if (reset_req)
    {
        reset_req  = 0;
        start_req  = 0;
        state      = TMR_IDLE;
        elapsed_ms = 0;
    }
    else if (start_req)
    {
        start_req  = 0;
        elapsed_ms = 0;
        if (0U != set_time_ms)        /* set value 000 = hold: never runs */
        {
            state = TMR_RUNNING;      /* START always restarts from zero */
        }
        else
        {
            state = TMR_IDLE;         /* START with set value 000 = hold: never runs */
        }

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

U32 tmr_get_elapsed_ms(void)
{
    return elapsed_ms;
}

U32 tmr_get_set_ms(void)
{
    return set_time_ms;
}
