/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (2)
#endif
/* ISR prototypes */
void r_icu_isr(void);
void tau_tmi_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_ICU_IRQ5 ((IRQn_Type) 7) /* ICU IRQ5 (External pin interrupt 5) */
#define ICU_IRQ5_IRQn          ((IRQn_Type) 7) /* ICU IRQ5 (External pin interrupt 5) */
#define VECTOR_NUMBER_TAU0_TMI00 ((IRQn_Type) 19) /* TAU0 TMI00 (End of timer channel 00 count or capture) */
#define TAU0_TMI00_IRQn          ((IRQn_Type) 19) /* TAU0 TMI00 (End of timer channel 00 count or capture) */
/* The number of entries required for the ICU vector table. */
#define BSP_ICU_VECTOR_NUM_ENTRIES (20)

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
