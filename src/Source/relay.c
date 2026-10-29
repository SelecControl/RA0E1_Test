/*
 * relay.c
 *
 *  Created on: Oct 22, 2026
 *      Author: Rohan S.
 */


#include "relay.h"
#include "hwdef.h"

/* Pin for each relay, in relay_id_t order */
static const bsp_io_port_pin_t relay_pins[RELAY_COUNT] = { RLY1, RLY2 };
static U8 relay_state[RELAY_COUNT] = { 0, 0 };     /* 1 = relay ON */

void relay_init(void)
{
    relay_off(RELAY_1);
    relay_off(RELAY_2);
}

/* Active LOW: pulling the pin to GND switches the relay ON */
void relay_on(relay_id_t id)
{
    if (id < RELAY_COUNT)
    {
        PIN_LOW(relay_pins[id]);
        relay_state[id] = 1U;
    }
}

/* HIGH = open drain released = relay OFF */
void relay_off(relay_id_t id)
{
    if (id < RELAY_COUNT)
    {
        PIN_HIGH(relay_pins[id]);
        relay_state[id] = 0U;
    }
}

U8 relay_is_on(relay_id_t id)
{
    return (id < RELAY_COUNT) ? relay_state[id] : 0U;
}
