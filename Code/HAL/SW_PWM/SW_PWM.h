#ifndef SW_PWM_H
#define SW_PWM_H

#include "../../MCAL/TIMERS/TIMERS_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../STD_LIBRARIES/STD_TYPES.h"



typedef enum{
    SW_PWM_NOT_OK=0,
    SW_PWM_OK,
    SW_PWM_NULL_PTR,
    SW_PWM_MAX_INVALID_LOAD_VALUE
}sw_pwm_enu_return_state_t;

typedef enum {
		PWM_OFF=0,
		PWM_ON
}sw_pwm_enu_pwm_state_t;

typedef struct{
	dio_enu_portx_t port_index;
	dio_enu_pinx_t pin_index;
	uint8_t duty_cycle;
	uint32_t frequency;
	uint16_t t_on;
	uint16_t cycle_duration;
	sw_pwm_enu_pwm_state_t pwm_state;
	uint64_t pwm_tick_ss;
}sw_pwm_configuration_t;

	
sw_pwm_enu_return_state_t pwm_init(sw_pwm_configuration_t *ptr_str_pwm_configuration);
sw_pwm_enu_return_state_t pwm_change_duty_cycle(sw_pwm_configuration_t *ptr_str_pwm_configuration);
void pwm_start_tick(void);
sw_pwm_enu_return_state_t pwm_start(sw_pwm_configuration_t *ptr_str_pwm_configuration);
sw_pwm_enu_return_state_t pwm_checking(sw_pwm_configuration_t *ptr_str_pwm_configuration);
sw_pwm_enu_return_state_t pwm_stop(sw_pwm_configuration_t *ptr_str_pwm_configuration);
void pwm_end_tick(void);

#endif