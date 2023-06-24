#include "SYSTICK_private.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_config.h"

#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"

static ptr_void_func systick_callback_func = NULL;

/**
 * @brief Initializes the SysTick timer.
 *
 * This function initializes the SysTick timer by configuring the clock source
 * based on the provided configuration.
 *
 * @param[in] ptr_str_systick_config Pointer to the configuration structure.
 * @return systick_enu_return_state_t Return status of the initialization process.
 *         - SYSTICK_OK: Initialization successful.
 *         - SYSTICK_NULL_PTR: Null pointer error.
 */
systick_enu_return_state_t systick_init(systick_str_systick_config_t *ptr_str_systick_config)
{
	systick_enu_return_state_t return_value = SYSTICK_OK;

	// Check if the provided pointer is not NULL
	if (ptr_str_systick_config != NULL)
	{
		// Configure the clock source for SysTick
		// Clear the CLKSOURCE bit in STK_CTRL and set it according to the enu_clock_source field
		STK_CTRL = (STK_CTRL & (~(1 << STK_CLKSOURCE))) | (ptr_str_systick_config->enu_clock_source << STK_CLKSOURCE);
	}
	else
	{
		// Return NULL pointer error
		return_value = SYSTICK_NULL_PTR;
	}

	// Return the status of the initialization process
	return return_value;
}

/**
 * @brief Sets the timeout value in milliseconds for the SysTick timer.
 *
 * This function calculates the appropriate value to be loaded into the SysTick
 * timer's LOAD register based on the provided timeout value in milliseconds.
 *
 * @param[in] time_out Timeout value in milliseconds.
 * @return systick_enu_return_state_t Return status of setting the timeout.
 *         - SYSTICK_OK: Setting the timeout successful.
 *         - SYSTICK_MAX_INVALID_LOAD_VALUE: Provided timeout value exceeds the maximum valid load value.
 */
systick_enu_return_state_t systick_set_timeout_ms(uint32_t time_out)
{
	systick_enu_return_state_t return_value = SYSTICK_OK;
	uint8_t prescaler = (READ_BIT(STK_CTRL, STK_CLKSOURCE) == SYSTICK_SYSCLK_CLOCK) ? 1 : 4;
	uint64_t max_load = 16777216;
	uint32_t tick_time_out = time_out / ((1 / ((double)SYS_CLK / prescaler)) * 1000);

	if (tick_time_out < max_load)
	{
		// Set the LOAD and VAL registers of SysTick
		STK_LOAD = tick_time_out - 1;
		STK_VAL = 0;
	}
	else
	{
		// Return error if the provided timeout value exceeds the maximum valid load value
		return_value = SYSTICK_MAX_INVALID_LOAD_VALUE;
	}

	// Return the status of setting the timeout
	return return_value;
}

/**
 * @brief Sets the callback function for the SysTick interrupt.
 *
 * This function sets the provided callback function to be called when the SysTick interrupt occurs.
 *
 * @param[in] ptr_callback_func Pointer to the callback function.
 * @return systick_enu_return_state_t Return status of setting the callback function.
 *         - SYSTICK_OK: Setting the callback function successful.
 *         - SYSTICK_NULL_PTR: Provided callback function pointer is NULL.
 */
systick_enu_return_state_t systick_set_callback(ptr_void_func ptr_callback_func)
{
	systick_enu_return_state_t return_value = SYSTICK_OK;
	if (ptr_callback_func != NULL)
	{
		// Set the callback function
		systick_callback_func = ptr_callback_func;
	}
	else
	{
		// Return error if the provided callback function pointer is NULL
		return_value = SYSTICK_NULL_PTR;
	}

	// Return the status of setting the callback function
	return return_value;
}

/**
 * @brief Enables the SysTick counter with optional interrupt.
 *
 * This function enables the SysTick counter and configures the interrupt based on the provided configuration.
 *
 * @param[in] ptr_str_systick_config Pointer to the SysTick configuration structure.
 * @return systick_enu_return_state_t Return status of enabling the SysTick counter.
 *         - SYSTICK_OK: SysTick counter enabled successfully.
 *         - SYSTICK_NULL_PTR: Provided configuration pointer is NULL.
 */
systick_enu_return_state_t systick_counter_enable(systick_str_systick_config_t *ptr_str_systick_config)
{
	systick_enu_return_state_t return_value = SYSTICK_OK;
	if (ptr_str_systick_config != NULL)
	{
		// Enable the SysTick counter
		SET_BIT(STK_CTRL, STK_ENABLE);

		if (ptr_str_systick_config->enu_int_state == SYSTICK_ENABLE_INT)
		{
			// Enable SysTick interrupt
			SET_BIT(STK_CTRL, STK_TICK_INT);
		}
		else
		{
			// Disable SysTick interrupt
			CLEAR_BIT(STK_CTRL, STK_TICK_INT);
		}
	}
	else
	{
		// Return error if the provided configuration pointer is NULL
		return_value = SYSTICK_NULL_PTR;
	}

	// Return the status of enabling the SysTick counter
	return return_value;
}

/**
 * @brief Disables the SysTick counter and interrupt.
 *
 * This function disables the SysTick counter and clears the interrupt.
 *
 * @param[in] ptr_str_systick_config Pointer to the SysTick configuration structure (unused).
 * @return systick_enu_return_state_t Return status of disabling the SysTick counter.
 *         - SYSTICK_OK: SysTick counter disabled successfully.
 *         - SYSTICK_NULL_PTR: Provided configuration pointer is NULL (unused).
 */
systick_enu_return_state_t systick_counter_disable(systick_str_systick_config_t *ptr_str_systick_config)
{
	systick_enu_return_state_t return_value = SYSTICK_OK;
	if (ptr_str_systick_config != NULL)
	{
		// Disable the SysTick counter
		CLEAR_BIT(STK_CTRL, STK_ENABLE);

		// Clear the SysTick interrupt
		CLEAR_BIT(STK_CTRL, STK_TICK_INT);
	}
	else
	{
		// Return error if the provided configuration pointer is NULL (unused)
		return_value = SYSTICK_NULL_PTR;
	}

	// Return the status of disabling the SysTick counter
	return return_value;
}

/**
 * @brief Retrieves the state of the SysTick counter.
 *
 * This function retrieves the state of the SysTick counter and updates the provided reach zero flag.
 *
 * @param[out] ptr_enu_reach_zero_flag Pointer to the reach zero flag to be updated.
 * @return systick_enu_return_state_t Return status of retrieving the SysTick counter state.
 *         - SYSTICK_OK: SysTick counter state retrieved successfully.
 *         - SYSTICK_NULL_PTR: Provided reach zero flag pointer is NULL.
 */
systick_enu_return_state_t systick_get_state(systick_enu_reach_zero_flag_t *ptr_enu_reach_zero_flag)
{
	systick_enu_return_state_t return_value = SYSTICK_OK;
	if (ptr_enu_reach_zero_flag != NULL)
	{
		// Check if the SysTick count flag is cleared
		if (READ_BIT(STK_CTRL, STK_COUNTFLAG) == 0)
		{
			*ptr_enu_reach_zero_flag = SYSTICK_NOT_REACH_FLAG; // Update the reach zero flag
		}
		else
		{
			*ptr_enu_reach_zero_flag = SYSTICK_REACH_FLAG; // Update the reach zero flag
		}
	}
	else
	{
		// Return error if the provided reach zero flag pointer is NULL
		return_value = SYSTICK_NULL_PTR;
	}

	// Return the status of retrieving the SysTick counter state
	return return_value;
}

/**
 * @brief SysTick interrupt handler.
 *
 * This function is called when the SysTick interrupt occurs. It checks if a callback function is registered
 * and invokes the callback function.
 *
 * @return None.
 */
void SysTick_Handler(void)
{
	if (systick_callback_func != NULL)
	{
		systick_callback_func(); // Invoke the callback function
	}
}
