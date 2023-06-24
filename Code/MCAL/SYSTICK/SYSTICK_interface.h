#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

#include "../../STD_LIBRARIES/STD_TYPES.h"

typedef void(*ptr_void_func)(void);

typedef enum{
	SYSTICK_NOT_REACH_FLAG=0,
  SYSTICK_REACH_FLAG=1
}systick_enu_reach_zero_flag_t;

typedef enum{
    SYSTICK_PIOSC_CLOCK_PRE_4=0,
    SYSTICK_SYSCLK_CLOCK
}systick_enu_clock_source_t;

typedef enum{
    SYSTICK_DISABLE_INT=0,
    SYSTICK_ENABLE_INT=1
}systick_enu_int_state_t;


typedef enum{
    SYSTICK_DISABLE_COUNTER=0,
    SYSTICK_ENABLE_COUNTER=1
}systick_enu_counter_state_t;


typedef struct{
	systick_enu_clock_source_t			enu_clock_source;
	systick_enu_int_state_t					enu_int_state;
	systick_enu_counter_state_t			enu_counter_state;
}systick_str_systick_config_t;

typedef enum{
    SYSTICK_NOT_OK=0,
    SYSTICK_OK,
    SYSTICK_NULL_PTR,
    SYSTICK_MAX_INVALID_LOAD_VALUE
}systick_enu_return_state_t;

systick_enu_return_state_t  systick_init(systick_str_systick_config_t *ptr_str_systick_config);
systick_enu_return_state_t  systick_set_timeout_ms(uint32_t time_out);
systick_enu_return_state_t  systick_set_callback(ptr_void_func ptr_callback_func);
systick_enu_return_state_t  systick_counter_enable(systick_str_systick_config_t *ptr_str_systick_config);
systick_enu_return_state_t  systick_counter_disable(systick_str_systick_config_t *ptr_str_systick_config);
systick_enu_return_state_t  systick_get_state(systick_enu_reach_zero_flag_t *ptr_enu_reach_zero_flag);
#endif