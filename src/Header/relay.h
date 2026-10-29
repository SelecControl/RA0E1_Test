/*
 * relay.h
 *
 *  Created on: Oct 22, 2026
 *      Author: Rohan S.
 */

#ifndef RELAY_H_
#define RELAY_H_

#include "typedef.h"

typedef enum
{
    RELAY_1 = 0,
    RELAY_2,
    RELAY_COUNT        /* always last = number of relays (2) */
} relay_id_t;

void relay_init(void);
void relay_on(relay_id_t id);
void relay_off(relay_id_t id);
U8   relay_is_on(relay_id_t id);

#endif /* RELAY_H_ */
