#ifndef APP_H
#define APP_H

#include "../HAL/LED/LED.h"
#include "../HAL/BUTTON/Button.h"
#include "../STD_LIBRARIES/bit_math.h"
#include "../STD_LIBRARIES/STD_TYPES.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../SERVICE/DELAY/DELAY.h"
#include "../HAL/SW_PWM/SW_PWM.h"
#include "../MCAL/SYS_CONTROL/SYS_CONTROL_interface.h"

typedef enum{
	GREEN_LED_OFF,
	GREEN_LED_DUTY_30,
	GREEN_LED_DUTY_60,
	GREEN_LED_DUTY_90,
	MAX_INVALID_LEDS_STATE
}app_enu_led_state_t;

void app_init(void);
void app_run(void);

#endif