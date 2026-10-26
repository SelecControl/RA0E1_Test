/*
 * din.h
 *
 *  Created on: Oct 23, 2026
 *      Author: SM 031
 */

#ifndef HEADER_DIN_H_
#define HEADER_DIN_H_

#include <stdint.h>

void     din_init(void);
void     din_1ms(void);                 /* call from the 1 ms timer interrupt           */
void     din_start_edge(void);          /* call from the START external-IRQ callback    */
uint16_t din_get_start_count(void);     /* START pulses since power-up (wraps at 65535) */
uint8_t  din_reset_active(void);        /* 1 = RESET terminal shorted (debounced)       */


#endif /* HEADER_DIN_H_ */
