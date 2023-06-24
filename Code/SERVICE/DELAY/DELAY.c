#include "DELAY.h"

static systick_str_systick_config_t g_str_systick_config;
static systick_enu_reach_zero_flag_t g_ptr_enu_reach_zero_flag;

void delay_ms(uint32_t copy_u32_time_out_ms){
	
	g_str_systick_config.enu_clock_source = SYSTICK_SYSCLK_CLOCK;
	g_str_systick_config.enu_int_state = SYSTICK_DISABLE_INT;
	
	systick_init(&g_str_systick_config);
	systick_set_timeout_ms(copy_u32_time_out_ms);
	
	systick_counter_enable(&g_str_systick_config);
	systick_get_state(&g_ptr_enu_reach_zero_flag);
	while(g_ptr_enu_reach_zero_flag == SYSTICK_NOT_REACH_FLAG){
		systick_get_state(&g_ptr_enu_reach_zero_flag);
	}
	systick_counter_disable(&g_str_systick_config);
}