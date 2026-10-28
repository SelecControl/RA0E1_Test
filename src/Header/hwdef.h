/*
 * hwdef.h
 *
 *  Created on: Oct 22, 2026
 *      Author: Rohan S.
 */

#ifndef HWDEF_H_
#define HWDEF_H_

#include "hal_data.h"

/* ---------------- Segment pins (PORT0) ---------------- */
#define SEGA    (BSP_IO_PORT_00_PIN_08)     /* pin 30 */
#define SEGB    (BSP_IO_PORT_00_PIN_09)     /* pin 29 */
#define SEGC    (BSP_IO_PORT_00_PIN_10)     /* pin 32 */
#define SEGD    (BSP_IO_PORT_00_PIN_11)     /* pin 31 */
#define SEGE    (BSP_IO_PORT_00_PIN_12)     /* pin 28 */
#define SEGF    (BSP_IO_PORT_00_PIN_13)     /* pin 27 */
#define SEGG    (BSP_IO_PORT_00_PIN_14)     /* pin 26 */
#define SEGDP   (BSP_IO_PORT_00_PIN_15)     /* pin 25 */

/* ---------------- Common-cathode (digit select) pins ---------------- */
#define CC1     (BSP_IO_PORT_01_PIN_00)     /* pin 24 */
#define CC2     (BSP_IO_PORT_01_PIN_01)     /* pin 23 */
#define CC3     (BSP_IO_PORT_01_PIN_02)     /* pin 22 */
#define CC4     (BSP_IO_PORT_01_PIN_03)     /* pin 21 */
#define CC5     (BSP_IO_PORT_01_PIN_09)     /* pin 18 */
#define CC6     (BSP_IO_PORT_01_PIN_10)     /* pin 19 */
#define CC7     (BSP_IO_PORT_01_PIN_12)     /* pin 20 - LED slot */

/* ---------------- Relay output pins (N-ch open drain, LOW = relay ON) ---------------- */
#define RLY1    (BSP_IO_PORT_09_PIN_13)     /* pin 10 -> terminals 3,4,5  (NO1, COM1, NC1) */
#define RLY2    (BSP_IO_PORT_09_PIN_14)     /* pin 9  -> terminals 8,9,10 (NC2, COM2, NO2) */

/* ---------------- Key return line ---------------- */
#define KBD_RET (BSP_IO_PORT_02_PIN_00)     /* pin 15, input only, LOW = key on active CC pressed */

/* ---------------- Digital inputs (terminals, LOW = shorted = active) ---------------- */
#define DI_START    (BSP_IO_PORT_02_PIN_01)     /* pin 14, IRQ5 external interrupt */
#define DI_RESET    (BSP_IO_PORT_02_PIN_14)     /* pin 3,  input only, polled      */

/* ---------------- Pin helper macros ---------------- */
#define PIN_HIGH(pin)   (R_IOPORT_PinWrite(&g_ioport_ctrl, (pin), BSP_IO_LEVEL_HIGH))
#define PIN_LOW(pin)    (R_IOPORT_PinWrite(&g_ioport_ctrl, (pin), BSP_IO_LEVEL_LOW))


#endif /* HWDEF_H_ */
