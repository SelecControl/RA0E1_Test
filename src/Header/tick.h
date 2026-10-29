/*
 * tick.h
 *
 *  Created on: Oct 29, 2026
 *      Author: Rohan S.
 */

#ifndef HEADER_TICK_H_
#define HEADER_TICK_H_

#include "typedef.h"

void tick_1ms(void);        /* call from the 1 ms timer interrupt        */
U32  tick_get_ms(void);     /* ms since power-up (wraps after ~49 days)  */


#endif /* HEADER_TICK_H_ */
