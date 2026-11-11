/*
 * keys.h
 *
 *  Created on: Nov 6, 2026
 *      Author: SM 031
 */

#ifndef HEADER_KEYS_H_
#define HEADER_KEYS_H_

#include "typedef.h"


#define KEY_EVT_SHORT (1U)
#define KEY_EVT_LONG (2U)
#define SET_KEY (1U)
#define PRG_KEY (2U)
#define RST_KEY (4U)

void key_sample(void);      /* called from the 1 ms interrupt */
U8 key_get_pressed(void);  /* returns the key which is pressed */
U8 key_get_event(void);

#endif /* HEADER_KEYS_H_ */
