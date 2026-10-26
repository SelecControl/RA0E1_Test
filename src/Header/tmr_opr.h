/*
 * tmr_opr.h
 *
 *  Created on: Oct 26, 2026
 *      Author: Rohan S.
 */

#ifndef HEADER_TMR_OPR_H_
#define HEADER_TMR_OPR_H_

#include <stdint.h>

typedef enum
{
    TMR_IDLE = 0,       /* waiting for START              */
    TMR_RUNNING,        /* timing in progress             */
    TMR_DONE            /* set time reached, output ON    */
} tmr_state_t;

void        tmr_init(uint32_t set_ms);
void        tmr_1ms(void);              /* call from the 1 ms timer interrupt */
void        tmr_start(void);            /* request: start timing from zero    */
void        tmr_reset(void);            /* request: stop and clear            */
tmr_state_t tmr_get_state(void);
uint32_t    tmr_get_elapsed_ms(void);
uint32_t    tmr_get_set_ms(void);

#endif /* HEADER_TMR_OPR_H_ */
