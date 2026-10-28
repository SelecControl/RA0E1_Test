/*
 * keys.h
 *
 *  Created on: Oct 23, 2026
 *      Author: Rohan S.
 */

#ifndef KEYS_H_
#define KEYS_H_

#include "typedef.h"

#define NUM_KEYS        (3U)        /* keys sit on CC1, CC2, CC3 */

/* Key bits as returned by key_get_state() */
#define KEY_SET         (1U << 0)   /* SW1 - CC1 - SET  (square)    */
#define KEY_DOWN        (1U << 1)   /* SW2 - CC2 - PROG (down)      */
#define KEY_UP          (1U << 2)   /* SW3 - CC3 - RST  (up)        */

/* Key events, produced once per press */
typedef enum
{
    KEY_EVT_NONE = 0,
    KEY_EVT_SET_SHORT,              /* 1 : SET  tapped                     */
    KEY_EVT_DOWN_SHORT,             /* 2 : DOWN tapped                     */
    KEY_EVT_UP_SHORT,               /* 3 : UP   tapped                     */
    KEY_EVT_SET_LONG,               /* 4 : SET  held 3 s                   */
    KEY_EVT_DOWN_LONG,              /* 5 : DOWN held 3 s (config mode)     */
    KEY_EVT_UP_LONG,                /* 6 : UP   held 3 s (reset)           */
    KEY_EVT_UP_DOWN_LONG            /* 7 : UP + DOWN held 3 s (protection) */
} key_event_t;

void        key_init(void);
void        key_sample(U8 cc_index);   /* called from the 1 ms interrupt */
U8     key_get_state(void);            /* debounced: bit0 = key on CC1, bit1 = CC2, bit2 = CC3 */
key_event_t key_get_event(void);            /* returns next event once, then KEY_EVT_NONE */


#endif /* KEYS_H_ */
