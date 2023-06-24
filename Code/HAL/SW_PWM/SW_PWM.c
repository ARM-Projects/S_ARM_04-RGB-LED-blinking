#include "SW_PWM.h"
static uint64_t MAX_VALUE_UINT32 = 4294967296;
static uint64_t pwm_tick = 0;
static timers_str_timer_config_t sw_pwm_timer0_a;

// Function: sw_pwm_tick_counter
// Description: Increments the PWM tick counter.
// Note: This function is likely to be used as a callback function for a timer interrupt.
static void sw_pwm_tick_counter(void)
{
	pwm_tick++;
}

// Function: pwm_init
// Description: Initializes a PWM (Pulse Width Modulation) configuration and sets up the corresponding pins.
//              Calculates the cycle duration and duty cycle based on the provided frequency and duty cycle percentage.
// Parameters:
//   - ptr_str_pwm_configuration: Pointer to the PWM configuration structure.
// Return:
//   - sw_pwm_enu_return_state_t: Return state indicating the success or failure of the initialization.

sw_pwm_enu_return_state_t pwm_init(sw_pwm_configuration_t *ptr_str_pwm_configuration)
{
	sw_pwm_enu_return_state_t return_value = SW_PWM_OK;
	dio_str_pin_Config_t l_pin_config_temp;

	// Check if the PWM configuration pointer is NULL
	if (ptr_str_pwm_configuration == NULL)
	{
		return_value = SW_PWM_NOT_OK;
	}
	else
	{
		// Configure the pin settings based on the PWM configuration
		l_pin_config_temp.enu_port = ptr_str_pwm_configuration->port_index;
		l_pin_config_temp.enu_pin = ptr_str_pwm_configuration->pin_index;
		l_pin_config_temp.enu_pin_mode = DIO_PIN_OUTPUT;
		l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_2MA;
		l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE;

		// Enable clock for the specified port
		dio_enable_clock(ptr_str_pwm_configuration->port_index);

		// Initialize the pin with the configured settings
		dio_init_pin(&l_pin_config_temp);

		// Calculate cycle duration and duty cycle based on frequency and percentage
		ptr_str_pwm_configuration->cycle_duration = (1 / (double)ptr_str_pwm_configuration->frequency) * 1000;
		ptr_str_pwm_configuration->t_on = (((double)ptr_str_pwm_configuration->duty_cycle) / 100) * (ptr_str_pwm_configuration->cycle_duration);

		// Set the PWM state to "off"
		ptr_str_pwm_configuration->pwm_state = PWM_OFF;
	}

	return return_value;
}

// Function: pwm_change_duty_cycle
// Description: Changes the duty cycle of a PWM configuration.
// Parameters:
//   - ptr_str_pwm_configuration: Pointer to the PWM configuration structure.
// Return:
//   - sw_pwm_enu_return_state_t: Return state indicating the success or failure of changing the duty cycle.

sw_pwm_enu_return_state_t pwm_change_duty_cycle(sw_pwm_configuration_t *ptr_str_pwm_configuration)
{
	sw_pwm_enu_return_state_t return_value = SW_PWM_OK;
	dio_str_pin_Config_t l_pin_config_temp;

	// Check if the PWM configuration pointer is NULL
	if (ptr_str_pwm_configuration == NULL)
	{
		return_value = SW_PWM_NOT_OK;
	}
	else
	{
		// Calculate the new "on" time based on the provided duty cycle
		ptr_str_pwm_configuration->t_on = (((double)ptr_str_pwm_configuration->duty_cycle) / 100) * (ptr_str_pwm_configuration->cycle_duration);
	}

	return return_value;
}

// Function: pwm_start_tick
// Description: Starts the PWM tick by initializing and enabling a timer with the specified configuration.
// Note: This function assumes the existence of the `sw_pwm_timer0_a` variable and uses it for timer configuration.

void pwm_start_tick(void)
{
	sw_pwm_timer0_a.timer_a_b = TIMER_A;
	sw_pwm_timer0_a.timer_bit_resolution = TIMER_16_32;
	sw_pwm_timer0_a.timer_index = TIMER_0_16;
	sw_pwm_timer0_a.timer_mode = TIMER_PERIODIC;
	sw_pwm_timer0_a.timer_counting_mode = TIIMER_COUNT_DOWN;

	// Initialize the timer with the specified configuration
	timers_init(&sw_pwm_timer0_a);

	// Set the timeout of the timer to 1 millisecond
	timers_set_timeout_ms(&sw_pwm_timer0_a, 1);

	// Set the callback function to be called on timer interrupt
	timers_set_callback(&sw_pwm_timer0_a, sw_pwm_tick_counter);

	// Enable the timer to start counting
	timers_enable(&sw_pwm_timer0_a);
}

// Function: pwm_start
// Description: Starts the PWM by configuring the pin and setting the initial state.
// Parameters:
//   - ptr_str_pwm_configuration: Pointer to the PWM configuration structure.
// Return:
//   - sw_pwm_enu_return_state_t: Return state indicating the success or failure of starting the PWM.

sw_pwm_enu_return_state_t pwm_start(sw_pwm_configuration_t *ptr_str_pwm_configuration)
{
	sw_pwm_enu_return_state_t return_value = SW_PWM_OK;
	dio_str_pin_Config_t l_pin_config_temp;

	// Check if the PWM configuration pointer is NULL
	if (ptr_str_pwm_configuration == NULL)
	{
		return_value = SW_PWM_NOT_OK;
	}
	else
	{
		// Configure the pin settings based on the PWM configuration
		l_pin_config_temp.enu_port = ptr_str_pwm_configuration->port_index;
		l_pin_config_temp.enu_pin = ptr_str_pwm_configuration->pin_index;
		l_pin_config_temp.enu_pin_mode = DIO_PIN_OUTPUT;
		l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_2MA;
		l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_HIGH_STATE;

		// Set the PWM state to "on"
		ptr_str_pwm_configuration->pwm_state = PWM_ON;

		// Set the pin to the high state
		dio_set_pin(&l_pin_config_temp, DIO_PIN_HIGH_STATE);

		// Store the current PWM tick value
		ptr_str_pwm_configuration->pwm_tick_ss = pwm_tick;
	}

	return return_value;
}

// Function: pwm_checking
// Description: Checks the current status of the PWM and performs necessary actions based on the elapsed time.
// Parameters:
//   - ptr_str_pwm_configuration: Pointer to the PWM configuration structure.
// Return:
//   - sw_pwm_enu_return_state_t: Return state indicating the success or failure of the PWM checking.

sw_pwm_enu_return_state_t pwm_checking(sw_pwm_configuration_t *ptr_str_pwm_configuration)
{
	sw_pwm_enu_return_state_t return_value = SW_PWM_OK;
	dio_str_pin_Config_t l_pin_config_temp;
	uint64_t pwm_tick_temp = pwm_tick, actual_time = 0;

	// Check if the PWM configuration pointer is NULL
	if (ptr_str_pwm_configuration == NULL)
	{
		return_value = SW_PWM_NOT_OK;
	}
	else
	{
		// Calculate the actual elapsed time since the previous check
		if (ptr_str_pwm_configuration->pwm_tick_ss > pwm_tick_temp)
		{
			actual_time = MAX_VALUE_UINT32 - ptr_str_pwm_configuration->pwm_tick_ss + pwm_tick_temp;
		}
		else
		{
			actual_time = pwm_tick_temp - ptr_str_pwm_configuration->pwm_tick_ss;
		}

		// Compare the elapsed time with the "on" time and cycle duration to determine the action
		if (ptr_str_pwm_configuration->t_on > actual_time)
		{
			// If the elapsed time is less than the "on" time and the PWM state is not "on", set the pin to the high state
			if (ptr_str_pwm_configuration->pwm_state != PWM_ON)
			{
				l_pin_config_temp.enu_port = ptr_str_pwm_configuration->port_index;
				l_pin_config_temp.enu_pin = ptr_str_pwm_configuration->pin_index;
				l_pin_config_temp.enu_pin_mode = DIO_PIN_OUTPUT;
				l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_4MA;
				l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_HIGH_STATE;

				ptr_str_pwm_configuration->pwm_state = PWM_ON;

				dio_set_pin(&l_pin_config_temp, DIO_PIN_HIGH_STATE);
			}
		}
		else if (ptr_str_pwm_configuration->cycle_duration > actual_time)
		{
			// If the elapsed time is greater than or equal to the "on" time but less than the cycle duration,
			// and the PWM state is not "off", set the pin to the low state
			if (ptr_str_pwm_configuration->pwm_state != PWM_OFF)
			{
				l_pin_config_temp.enu_port = ptr_str_pwm_configuration->port_index;
				l_pin_config_temp.enu_pin = ptr_str_pwm_configuration->pin_index;
				l_pin_config_temp.enu_pin_mode = DIO_PIN_OUTPUT;
				l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_4MA;
				l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE;

				ptr_str_pwm_configuration->pwm_state = PWM_OFF;
				dio_set_pin(&l_pin_config_temp, DIO_PIN_LOW_STATE);
			}
		}
		else
		{
			// If the elapsed time is greater than or equal to the cycle duration,
			// update the stored PWM tick value to the current tick
			ptr_str_pwm_configuration->pwm_tick_ss = pwm_tick_temp;
		}
	}

	return return_value;
}

// Function: pwm_stop
// Description: Stops the PWM and resets the configuration.
// Parameters:
//   - ptr_str_pwm_configuration: Pointer to the PWM configuration structure.
// Return:
//   - sw_pwm_enu_return_state_t: Return state indicating the success or failure of stopping the PWM.

sw_pwm_enu_return_state_t pwm_stop(sw_pwm_configuration_t *ptr_str_pwm_configuration)
{
	sw_pwm_enu_return_state_t return_value = SW_PWM_OK;
	dio_str_pin_Config_t l_pin_config_temp;

	// Check if the PWM configuration pointer is NULL
	if (ptr_str_pwm_configuration == NULL)
	{
		return_value = SW_PWM_NOT_OK;
	}
	else
	{
		// Configure the pin and set it to the low state
		l_pin_config_temp.enu_port = ptr_str_pwm_configuration->port_index;
		l_pin_config_temp.enu_pin = ptr_str_pwm_configuration->pin_index;
		l_pin_config_temp.enu_pin_mode = DIO_PIN_OUTPUT;
		l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_4MA;
		l_pin_config_temp.un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE;

		ptr_str_pwm_configuration->pwm_state = PWM_OFF;
		dio_set_pin(&l_pin_config_temp, DIO_PIN_LOW_STATE);

		// Reset the stored PWM tick value
		ptr_str_pwm_configuration->pwm_tick_ss = 0;
	}

	return return_value;
}

// Function: pwm_end_tick
// Description: Ends the PWM tick by disabling the timer.
// Parameters: None
// Return: None

void pwm_end_tick()
{
	timers_disable(&sw_pwm_timer0_a);
}
