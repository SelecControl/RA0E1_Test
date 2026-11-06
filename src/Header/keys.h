/*
 * keys.h
 *
 *  Created on: Nov 6, 2026
 *      Author: SM 031
 */

#ifndef HEADER_KEYS_H_
#define HEADER_KEYS_H_

#include "typedef.h"

void key_sample(void);      /* called from the 1 ms interrupt */
U8 key_get_bits(void);  /* returns the key bits */

#endif /* HEADER_KEYS_H_ */
