/* generated HAL source file - do not edit */
#include "hal_data.h"
tau_instance_ctrl_t g_timer_1ms_ctrl;
const tau_extended_cfg_t g_timer_1ms_extend =
{ .opirq = TAU_INTERRUPT_OPIRQ_BIT_RESET,
  .tau_func = TAU_FUNCTION_INTERVAL,
  .bit_mode = TAU_BIT_MODE_16BIT,
  .initial_output = TAU_PIN_OUTPUT_CFG_DISABLED,
  .input_source = TAU_INPUT_SOURCE_NONE,
  .tau_filter = TAU_INPUT_NOISE_FILTER_DISABLE,
  .trigger_edge = TAU_TRIGGER_EDGE_RISING,
  .operation_clock = TAU_OPERATION_CK00,
  /* Not used for 16-bit or lower 8-bit mode */
  .period_higher_8bit_counts = (uint16_t) 0x100,
  .higher_8bit_cycle_end_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_TAU0_TMI00H)
    .higher_8bit_cycle_end_irq       = VECTOR_NUMBER_TAU0_TMI00H,
#else
  .higher_8bit_cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
const timer_cfg_t g_timer_1ms_cfg =
{ .mode = (timer_mode_t) 0,
/* Actual Period: 0.0010000000 seconds. */
/* Minimum Period ~ Maximum Period: 0.0000001000 ~ 0.00327680 seconds. */.period_counts = (uint32_t) 0x4e20,
  .duty_cycle_counts = 0, .source_div = (timer_source_div_t) BSP_CFG_TAU_CK00, .channel = 0, .p_callback =
          tau_1ms_callback,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = (void*) &NULL,
#endif
  .p_extend = &g_timer_1ms_extend,
  .cycle_end_ipl = (1),
#if defined(VECTOR_NUMBER_TAU0_TMI00)
    .cycle_end_irq       = VECTOR_NUMBER_TAU0_TMI00,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer_1ms =
{ .p_ctrl = &g_timer_1ms_ctrl, .p_cfg = &g_timer_1ms_cfg, .p_api = &g_timer_on_tau };
void g_hal_init(void)
{
    g_common_init ();
}
