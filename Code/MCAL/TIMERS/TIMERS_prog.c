#include "TIMERS_private.h"
#include "TIMERS_interface.h"
#include "TIMERS_config.h"
#include "../NVIC/NVIC_interface.h"
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"

/**
 * Enables the clock for the specified timer.
 *
 * @param copy_enu_timer_index The timer index for which the clock will be enabled.
 */
static void timers_enable_clock(timers_enu_timer_index_t copy_enu_timer_index)
{
	if (copy_enu_timer_index <= TIMER_5_16)
	{
		SET_BIT(RCGCTIMER, copy_enu_timer_index);
	}
	else if (copy_enu_timer_index <= TIMER_11_32)
	{
		SET_BIT(RCGCTIMER, (copy_enu_timer_index - 6));
	}
	else
	{
		// Invalid timer index
	}
}

/**
 * Retrieves the base address of the specified timer.
 *
 * @param copy_enu_timer_index The timer index for which the base address will be retrieved.
 * @return The base address of the specified timer.
 */
static uint32_t timers_get_base_address(timers_enu_timer_index_t copy_enu_timer_index)
{
	uint32_t l_timer_base_address = 0;
	switch (copy_enu_timer_index)
	{
	case TIMER_0_16:
		l_timer_base_address = TIMER_0;
		break;
	case TIMER_1_16:
		l_timer_base_address = TIMER_1;
		break;
	case TIMER_2_16:
		l_timer_base_address = TIMER_2;
		break;
	case TIMER_3_16:
		l_timer_base_address = TIMER_3;
		break;
	case TIMER_4_16:
		l_timer_base_address = TIMER_4;
		break;
	case TIMER_5_16:
		l_timer_base_address = TIMER_5;
		break;
	case TIMER_6_32:
		l_timer_base_address = WIDE_TIMER_0;
		break;
	case TIMER_7_32:
		l_timer_base_address = WIDE_TIMER_1;
		break;
	case TIMER_8_32:
		l_timer_base_address = WIDE_TIMER_2;
		break;
	case TIMER_9_32:
		l_timer_base_address = WIDE_TIMER_3;
		break;
	case TIMER_10_32:
		l_timer_base_address = WIDE_TIMER_4;
		break;
	case TIMER_11_32:
		l_timer_base_address = WIDE_TIMER_5;
		break;
	default:
		// Invalid timer index
		break;
	}
	return l_timer_base_address;
}

/**
 * Retrieves the interrupt number associated with the specified timer and timer A/B.
 *
 * @param copy_enu_timer_index The timer index.
 * @param copy_enu_timer_a_b The timer A/B selection.
 * @return The interrupt number associated with the specified timer and timer A/B.
 */
static nvic_enu_interupt_index_t timers_int_number(timers_enu_timer_index_t copy_enu_timer_index, timers_enu_timer_a_b_t copy_enu_timer_a_b)
{
	nvic_enu_interupt_index_t l_enu_timer_int_number;
	if (copy_enu_timer_a_b == TIMER_A)
	{
		switch (copy_enu_timer_index)
		{
		case TIMER_0_16:
			l_enu_timer_int_number = Timer_0_A;
			break;
		case TIMER_1_16:
			l_enu_timer_int_number = Timer_1_A;
			break;
		case TIMER_2_16:
			l_enu_timer_int_number = Timer_2_A;
			break;
		default:
			// Invalid timer index
			break;
		}
	}
	else if (copy_enu_timer_a_b == TIMER_B)
	{
		switch (copy_enu_timer_index)
		{
		case TIMER_0_16:
			l_enu_timer_int_number = Timer_0_B;
			break;
		case TIMER_1_16:
			l_enu_timer_int_number = Timer_1_B;
			break;
		case TIMER_2_16:
			l_enu_timer_int_number = Timer_2_B;
			break;
		default:
			// Invalid timer index
			break;
		}
	}
	else
	{
		// Invalid timer A/B selection
	}
	return l_enu_timer_int_number;
}

/**
 * Initializes the timer based on the provided configuration.
 *
 * @param ptr_str_timer_config Pointer to the timer configuration structure.
 * @return The return state of the timer initialization.
 */
timers_enu_return_state_t timers_init(timers_str_timer_config_t *ptr_str_timer_config)
{
	timers_enu_return_state_t return_value = TIMERS_OK;
	uint32_t l_timer_base_address = 0;
	nvic_enu_interupt_index_t l_enu_timer_int_number;

	if (ptr_str_timer_config != NULL)
	{
		// Enable clock for the specified timer
		timers_enable_clock(ptr_str_timer_config->timer_index);

		// Get the interrupt number for the specified timer and timer A/B
		l_enu_timer_int_number = timers_int_number(ptr_str_timer_config->timer_index, ptr_str_timer_config->timer_a_b);

		// Enable the interrupt for the timer
		nvic_EnablePeripheral(l_enu_timer_int_number);

		// Get the base address of the timer
		l_timer_base_address = timers_get_base_address(ptr_str_timer_config->timer_index);

		// Disable timer A
		CLEAR_BIT(HWREG32((l_timer_base_address + GPTMCTL)), TAEN);

		// Set the timer bit resolution
		HWREG32((l_timer_base_address + GPTMCFG)) = ((HWREG32(l_timer_base_address + GPTMCFG) & (~0b111)) | ptr_str_timer_config->timer_bit_resolution);

		// Set the timer mode
		HWREG32((l_timer_base_address + GPTMTAMR)) = ((HWREG32(l_timer_base_address + GPTMTAMR) & (~0b11)) | ptr_str_timer_config->timer_mode);

		// Set the timer counting mode
		HWREG32((l_timer_base_address + GPTMTAMR)) = ((HWREG32(l_timer_base_address + GPTMTAMR) & (~(1 << TACDIR))) | (ptr_str_timer_config->timer_counting_mode << TACDIR));

		// Clear the timer timeout interrupt
		SET_BIT(HWREG32((l_timer_base_address + GPTMICR)), TATOCINT);

		// Enable the timer timeout interrupt
		SET_BIT(HWREG32((l_timer_base_address + GPTMIMR)), TATOIM);
	}
	else
	{
		// Null pointer provided
		return_value = TIMERS_NULL_PTR;
	}

	return return_value;
}

/**
 * Sets the timeout value in milliseconds for the specified timer.
 *
 * @param ptr_str_timer_config Pointer to the timer configuration structure.
 * @param copy_u32_time_out Timeout value in milliseconds.
 * @return The return state of the timeout setting.
 */
timers_enu_return_state_t timers_set_timeout_ms(timers_str_timer_config_t *ptr_str_timer_config, uint32_t copy_u32_time_out)
{
	timers_enu_return_state_t return_value = TIMERS_OK;
	uint32_t l_timer_base_address = 0;
	uint32_t prescaler = 0;
	uint64_t l_max_load = 65536;
	uint32_t tick_time_out;

	l_timer_base_address = timers_get_base_address(ptr_str_timer_config->timer_index);

	// Calculate the prescaler value
	prescaler = (HWREG32((l_timer_base_address + GPTMTAPR)) & 0x0000FFFF) + 1;

	// Calculate the tick timeout value
	tick_time_out = (copy_u32_time_out / ((1 / ((double)TIMERS_CLOCK / prescaler)) * 1000));

	if (tick_time_out < l_max_load)
	{
		// Set the tick timeout value
		HWREG32((l_timer_base_address + GPTMTAILR)) = tick_time_out;
	}
	else
	{
		// Timeout value exceeds the maximum load value
		return_value = TIMERS_MAX_INVALID_LOAD_VALUE;
	}

	return return_value;
}

/**
 * Sets the timeout value in microseconds for the specified timer.
 *
 * @param ptr_str_timer_config Pointer to the timer configuration structure.
 * @param copy_u32_time_out Timeout value in microseconds.
 * @return The return state of the timeout setting.
 */
timers_enu_return_state_t timers_set_timeout_us(timers_str_timer_config_t *ptr_str_timer_config, uint32_t copy_u32_time_out)
{
	timers_enu_return_state_t return_value = TIMERS_OK;
	uint32_t l_timer_base_address = 0;
	uint32_t prescaler = 0;
	uint64_t l_max_load = 65536;
	uint32_t tick_time_out;

	l_timer_base_address = timers_get_base_address(ptr_str_timer_config->timer_index);

	// Calculate the prescaler value
	prescaler = (HWREG32((l_timer_base_address + GPTMTAPR)) & 0x0000FFFF) + 1;

	// Calculate the tick timeout value
	tick_time_out = 65535 - (copy_u32_time_out / ((1 / ((double)TIMERS_CLOCK / prescaler)) * 1000 * 1000));

	if (tick_time_out < l_max_load)
	{
		// Set the tick timeout value
		HWREG32((l_timer_base_address + GPTMTAILR)) = tick_time_out;
	}
	else
	{
		// Timeout value exceeds the maximum load value
		return_value = TIMERS_MAX_INVALID_LOAD_VALUE;
	}

	return return_value;
}

/**
 * Sets the callback function for the specified timer.
 *
 * @param ptr_str_timer_config Pointer to the timer configuration structure.
 * @param ptr_callback_func Pointer to the callback function.
 * @return The return state of setting the callback function.
 */
timers_enu_return_state_t timers_set_callback(timers_str_timer_config_t *ptr_str_timer_config, ptr_void_func ptr_callback_func)
{
	timers_enu_return_state_t return_value = TIMERS_OK;

	if (ptr_callback_func != NULL)
	{
		// Set the callback function
		timer_callback_func[0] = ptr_callback_func;
	}
	else
	{
		// Null pointer provided for the callback function
		return_value = TIMERS_NULL_PTR;
	}

	return return_value;
}

/**
 * Enables the specified timer.
 *
 * @param ptr_str_timer_config Pointer to the timer configuration structure.
 * @return The return state of enabling the timer.
 */
timers_enu_return_state_t timers_enable(timers_str_timer_config_t *ptr_str_timer_config)
{
	timers_enu_return_state_t return_value = TIMERS_OK;
	uint32_t l_timer_base_address = 0;

	if (ptr_str_timer_config != NULL)
	{
		l_timer_base_address = timers_get_base_address(ptr_str_timer_config->timer_index);
		SET_BIT(HWREG32((l_timer_base_address + GPTMCTL)), TAEN);
	}
	else
	{
		// Null pointer provided for the timer configuration structure
		return_value = TIMERS_NULL_PTR;
	}

	return return_value;
}

/**
 * Disables the specified timer.
 *
 * @param ptr_str_timer_config Pointer to the timer configuration structure.
 * @return The return state of disabling the timer.
 */
timers_enu_return_state_t timers_disable(timers_str_timer_config_t *ptr_str_timer_config)
{
	timers_enu_return_state_t return_value = TIMERS_OK;
	uint32_t l_timer_base_address = 0;

	if (ptr_str_timer_config != NULL)
	{
		l_timer_base_address = timers_get_base_address(ptr_str_timer_config->timer_index);
		CLEAR_BIT(HWREG32((l_timer_base_address + GPTMCTL)), TAEN);
	}
	else
	{
		// Null pointer provided for the timer configuration structure
		return_value = TIMERS_NULL_PTR;
	}

	return return_value;
}

/**
 * TIMER0A interrupt handler.
 * This function is called when the Timer 0A interrupt occurs.
 */
void TIMER0A_Handler(void)
{
	if (READ_BIT(HWREG32((TIMER_0 + GPTMMIS)), TATOMIS))
	{
		// Timer A Time-Out interrupt occurred

		if (timer_callback_func[0] != NULL)
		{
			// Execute the callback function if it is not NULL
			timer_callback_func[0]();
		}

		// Clear the Timer A Time-Out Interrupt (TATOCINT) flag
		SET_BIT(HWREG32((TIMER_0 + GPTMICR)), TATOCINT);
	}
}
