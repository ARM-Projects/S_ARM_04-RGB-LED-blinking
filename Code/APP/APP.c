
#include "APP.h"


static sys_control_str_config_t str_sys_control_config;
static sw_pwm_configuration_t green_led;

static button_str_btn_config_t btn_1;

void app_init(void)
{
	// Configure Clock System
	sys_control_str_config_t sys_control_config;
	sys_control_config.enu_OSCSRC = SYS_CONTROL_PIOSC;
	sys_control_config.prescaller = 1;
	sys_control_set_clock_system(&sys_control_config);

	// Configure Green LED
	sw_pwm_configuration_t green_led;
	green_led.port_index = DIO_PORTF;
	green_led.pin_index = DIO_PIN_3;
	green_led.frequency = 2;
	green_led.duty_cycle = 0;
	pwm_init(&green_led);
	pwm_start_tick();
	pwm_start(&green_led);

	// Configure Button 1
	button_str_btn_config_t btn_1;
	btn_1.port_name = DIO_PORTF;
	btn_1.pin = DIO_PIN_4;
	btn_1.button_state = BUTTON_RELEASED;
	btn_1.button_active = BUTTON_ACTIVE_LOW;
	button_initialization(&btn_1);
}

void app_run(void){
	app_enu_led_state_t leds_state = GREEN_LED_OFF;
	btn_enu_btn_state_t btn_1_state;
	uint8_t state_changed_flag = 0;
	while(1){
		
		if(state_changed_flag == 1){
			state_changed_flag = 0;
			switch(leds_state){
					case GREEN_LED_OFF:
					green_led.duty_cycle = 0;
					pwm_change_duty_cycle(&green_led);
					break;
				case GREEN_LED_DUTY_30:
					green_led.duty_cycle = 30;
					pwm_change_duty_cycle(&green_led);
					break;
				case GREEN_LED_DUTY_60:
					green_led.duty_cycle = 60;
					pwm_change_duty_cycle(&green_led);
					break;
				case GREEN_LED_DUTY_90:
					green_led.duty_cycle = 90;
					pwm_change_duty_cycle(&green_led);
					break;
				default:
					break;
			}
			
		}
		button_read_state(&btn_1, &btn_1_state);
		if(btn_1_state == BUTTON_PRESSED){
			while(btn_1_state == BUTTON_PRESSED){
				button_read_state(&btn_1, &btn_1_state);
			}
			state_changed_flag = 1;
			leds_state++;
			if(leds_state == MAX_INVALID_LEDS_STATE){
			
				leds_state = GREEN_LED_OFF;
			}
		
		}
		
		pwm_checking(&green_led);

	}
	
}