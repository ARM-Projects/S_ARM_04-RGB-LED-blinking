#ifndef TIMERS_INTERFACE_H
#define TIMERS_INTERFACE_H

#include "../../STD_LIBRARIES/STD_TYPES.h"

typedef void(*ptr_void_func)(void);


typedef enum{
    TIIMER_COUNT_DOWN = 0,
		TIIMER_COUNT_UP = 1
		
}timers_enu_timer_counting_mode_t;

typedef enum{
    TIIMER_ONE_SHOT=1,
		TIMER_PERIODIC = 2,
		TIMER_CAPTURE = 3
}timers_enu_timer_mode_t;
typedef enum{
    TIMER_A=0,
		TIMER_CONCATINATED = 0,
		TIMER_B=1
}timers_enu_timer_a_b_t;
typedef enum{
    TIMER_32_64=0,
		TIMER_RTC_32_64 = 0x1,
		TIMER_16_32=0x4
}timers_enu_timer_bit_resolution_t;

typedef enum{
	TIMER_0_16=0,
	TIMER_1_16,
	TIMER_2_16,
	TIMER_3_16,
	TIMER_4_16,
	TIMER_5_16,
	TIMER_6_32,
	TIMER_7_32,
	TIMER_8_32,
	TIMER_9_32,
	TIMER_10_32,
	TIMER_11_32
}timers_enu_timer_index_t;

typedef enum{
	Timer_0_A_INT= 19,
	Timer_0_B_INT,
	Timer_1_A_INT,
	Timer_1_B_INT,
	Timer_2_A_INT,
	Timer_2_B_INT=24
}timers_enu_timer_int_number_t;

typedef struct{
	timers_enu_timer_index_t  timer_index;
	timers_enu_timer_bit_resolution_t		timer_bit_resolution;
	timers_enu_timer_mode_t		timer_mode;
	timers_enu_timer_a_b_t		timer_a_b;
	timers_enu_timer_counting_mode_t timer_counting_mode;
}timers_str_timer_config_t;

typedef enum{
    TIMERS_NOT_OK=0,
    TIMERS_OK,
    TIMERS_NULL_PTR,
    TIMERS_MAX_INVALID_LOAD_VALUE
}timers_enu_return_state_t;

timers_enu_return_state_t  timers_init(timers_str_timer_config_t *ptr_str_timer_config);
timers_enu_return_state_t  timers_set_timeout_ms(timers_str_timer_config_t *ptr_str_timer_config, uint32_t copy_u32_time_out);
timers_enu_return_state_t  timers_set_timeout_us(timers_str_timer_config_t *ptr_str_timer_config, uint32_t copy_u32_time_out);
timers_enu_return_state_t  timers_set_callback(timers_str_timer_config_t *ptr_str_timer_config, ptr_void_func ptr_callback_func);
timers_enu_return_state_t  timers_enable(timers_str_timer_config_t *ptr_str_timer_config);
timers_enu_return_state_t  timers_disable(timers_str_timer_config_t *ptr_str_timer_config);
#endif