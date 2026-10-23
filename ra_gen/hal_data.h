/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_tau.h"
#include "r_timer_api.h"
FSP_HEADER
/** TAU Timer Instance */
extern const timer_instance_t g_timer_1ms;

/** Access the TAU instance using these structures when calling API functions directly (::p_api is not used). */
extern tau_instance_ctrl_t g_timer_1ms_ctrl;
extern const timer_cfg_t g_timer_1ms_cfg;

#ifndef tau_1ms_callback
void tau_1ms_callback(timer_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
