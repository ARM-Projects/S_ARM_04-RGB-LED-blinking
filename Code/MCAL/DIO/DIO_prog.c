#include "DIO_private.h"
#include "DIO_interface.h"

#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"


/**
 * @brief Enables the clock for a specified port.
 * @param copy_enu_port_num The port number to enable the clock for.
 * @return dio_enu_return_state_t The return state of the function:
 *         - DIO_OK: The clock enable operation was successful.
 *         - Other possible return states indicating an error.
 */
dio_enu_return_state_t dio_enable_clock(dio_enu_portx_t copy_enu_port_num)
{
	dio_enu_return_state_t return_value = DIO_OK;

	if (copy_enu_port_num < MAX_INVALID_PORT)
	{
		// Set the corresponding bit in the RCGCGPIO register to enable the clock for the specified port
		SET_BIT(RCGCGPIO, copy_enu_port_num);
	}
	else
	{
		// Handle the case when an invalid port number is provided

		return_value = DIO_NOT_OK;
	}

	return return_value;
}
/**
 * @brief Initializes a pin based on the provided pin configuration.
 * @param ptr_str_pinconfig Pointer to the pin configuration structure.
 * @return dio_enu_return_state_t The return state of the function:
 *         - DIO_OK: The pin initialization was successful.
 *         - Other possible return states indicating an error.
 */
dio_enu_return_state_t dio_init_pin(dio_str_pin_Config_t *ptr_str_pinconfig)
{
	dio_enu_return_state_t return_value = DIO_OK;
	uint32_t l_un32_gpio_base_address = 0;
	dio_enu_output_current_t l_output_current;
	dio_enu_input_type_t l_enu_input_type;
	dio_enu_pin_state_t l_enu_pin_state;

	if (ptr_str_pinconfig != NULL)
	{
		switch (ptr_str_pinconfig->enu_port)
		{
		case DIO_PORTA:
			l_un32_gpio_base_address = DIO_PORTA_APB;
			break;
		case DIO_PORTB:
			l_un32_gpio_base_address = DIO_PORTB_APB;
			break;
		case DIO_PORTC:
			l_un32_gpio_base_address = DIO_PORTC_APB;
			break;
		case DIO_PORTD:
			l_un32_gpio_base_address = DIO_PORTD_APB;
			break;
		case DIO_PORTE:
			l_un32_gpio_base_address = DIO_PORTE_APB;
			break;
		case DIO_PORTF:
			l_un32_gpio_base_address = DIO_PORTF_APB;
			break;
		default:
			// Handle the case when an invalid port is provided

			break;
		}

		SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODEN), ptr_str_pinconfig->enu_pin);
		HWREG32(l_un32_gpio_base_address + GPIOPCTL) &= ~(((uint32_t)0xF) << (ptr_str_pinconfig->enu_pin * 4));

		if (ptr_str_pinconfig->enu_pin_mode == DIO_PIN_OUTPUT)
		{
			SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODIR), ptr_str_pinconfig->enu_pin);
			l_output_current = ptr_str_pinconfig->un_input_output_type.str_output_type_and_speed_and_state.enu_output_current;

			if (l_output_current == DIO_PIN_2MA)
			{
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODR2R), ptr_str_pinconfig->enu_pin);
			}
			else if (l_output_current == DIO_PIN_4MA)
			{
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODR4R), ptr_str_pinconfig->enu_pin);
			}
			else if (l_output_current == DIO_PIN_8MA)
			{
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODR8R), ptr_str_pinconfig->enu_pin);
			}
			else
			{
				// Handle the case when an invalid output current is provided
			}

			l_enu_pin_state = ptr_str_pinconfig->un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state;
			dio_set_pin(ptr_str_pinconfig, l_enu_pin_state);
		}
		else if (ptr_str_pinconfig->enu_pin_mode == DIO_PIN_INPUT)
		{
			CLEAR_BIT(HWREG32(l_un32_gpio_base_address + GPIODIR), ptr_str_pinconfig->enu_pin);
			l_enu_input_type = ptr_str_pinconfig->un_input_output_type.enu_input_type;

			if (l_enu_input_type == DIO_PIN_INPUT_PULL_UP)
			{
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPUR), ptr_str_pinconfig->enu_pin);
			}
			else if (l_enu_input_type == DIO_PIN_INPUT_PULL_DOWN)
			{
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPDR), ptr_str_pinconfig->enu_pin);
			}
			else
			{
				// Handle the case when an invalid input type is provided
			}
		}
		else
		{
			// Handle the case when an invalid pin mode is provided
		}
	}
	else
	{
		return_value = DIO_NULL_PTR;
	}

	return return_value;
}
/**
 * @brief Sets the state of a pin based on the provided pin configuration and pin state.
 * @param ptr_str_pinconfig Pointer to the pin configuration structure.
 * @param copy_enu_pin_state The state to set the pin to (DIO_PIN_HIGH_STATE or DIO_PIN_LOW_STATE).
 * @return dio_enu_return_state_t The return state of the function:
 *         - DIO_OK: The pin state was set successfully.
 *         - Other possible return states indicating an error.
 */
dio_enu_return_state_t dio_set_pin(dio_str_pin_Config_t *ptr_str_pinconfig, dio_enu_pin_state_t copy_enu_pin_state)
{
	dio_enu_return_state_t return_value = DIO_OK;
	uint32_t l_un32_gpio_base_address = 0;

	if (ptr_str_pinconfig != NULL)
	{
		switch (ptr_str_pinconfig->enu_port)
		{
		case DIO_PORTA:
			l_un32_gpio_base_address = DIO_PORTA_APB;
			break;
		case DIO_PORTB:
			l_un32_gpio_base_address = DIO_PORTB_APB;
			break;
		case DIO_PORTC:
			l_un32_gpio_base_address = DIO_PORTC_APB;
			break;
		case DIO_PORTD:
			l_un32_gpio_base_address = DIO_PORTD_APB;
			break;
		case DIO_PORTE:
			l_un32_gpio_base_address = DIO_PORTE_APB;
			break;
		case DIO_PORTF:
			l_un32_gpio_base_address = DIO_PORTF_APB;
			break;
		default:
			// Handle the case when an invalid port is provided
			// You can add appropriate error handling code here if needed
			break;
		}

		if (copy_enu_pin_state == DIO_PIN_HIGH_STATE)
		{
			HWREG32(l_un32_gpio_base_address + GPIODATA + (1 << (ptr_str_pinconfig->enu_pin + 2))) = (DIO_PIN_HIGH_STATE << ptr_str_pinconfig->enu_pin);
			SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPUR), ptr_str_pinconfig->enu_pin);
		}
		else if (copy_enu_pin_state == DIO_PIN_LOW_STATE)
		{
			HWREG32(l_un32_gpio_base_address + GPIODATA + (1 << (ptr_str_pinconfig->enu_pin + 2))) = DIO_PIN_LOW_STATE;
			SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPDR), ptr_str_pinconfig->enu_pin);
		}
	}
	else
	{
		return_value = DIO_NULL_PTR;
	}

	return return_value;
}

/**
 * @brief Toggles the state of a pin based on the provided pin configuration.
 * @param ptr_str_pinconfig Pointer to the pin configuration structure.
 * @return dio_enu_return_state_t The return state of the function:
 *         - DIO_OK: The pin state was toggled successfully.
 *         - Other possible return states indicating an error.
 */
dio_enu_return_state_t dio_toggle_pin(dio_str_pin_Config_t *ptr_str_pinconfig)
{
	dio_enu_return_state_t return_value = DIO_OK;
	uint32_t l_un32_gpio_base_address = 0;
	dio_enu_pin_state_t l_enu_pin_state;

	if (ptr_str_pinconfig != NULL)
	{
		switch (ptr_str_pinconfig->enu_port)
		{
		case DIO_PORTA:
			l_un32_gpio_base_address = DIO_PORTA_APB;
			break;
		case DIO_PORTB:
			l_un32_gpio_base_address = DIO_PORTB_APB;
			break;
		case DIO_PORTC:
			l_un32_gpio_base_address = DIO_PORTC_APB;
			break;
		case DIO_PORTD:
			l_un32_gpio_base_address = DIO_PORTD_APB;
			break;
		case DIO_PORTE:
			l_un32_gpio_base_address = DIO_PORTE_APB;
			break;
		case DIO_PORTF:
			l_un32_gpio_base_address = DIO_PORTF_APB;
			break;
		default:
			// Handle the case when an invalid port is provided
			break;
		}

		dio_read_pin(ptr_str_pinconfig, &l_enu_pin_state);
		if (l_enu_pin_state != DIO_PIN_HIGH_STATE)
		{
			HWREG32(l_un32_gpio_base_address + GPIODATA + (1 << (ptr_str_pinconfig->enu_pin + 2))) = (DIO_PIN_HIGH_STATE << ptr_str_pinconfig->enu_pin);
			SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPUR), ptr_str_pinconfig->enu_pin);
		}
		else if (l_enu_pin_state != DIO_PIN_LOW_STATE)
		{
			HWREG32(l_un32_gpio_base_address + GPIODATA + (1 << (ptr_str_pinconfig->enu_pin + 2))) = DIO_PIN_LOW_STATE;
			SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPDR), ptr_str_pinconfig->enu_pin);
		}
	}
	else
	{
		return_value = DIO_NULL_PTR;
	}

	return return_value;
}

/**
 * @brief Reads the state of a pin based on the provided pin configuration.
 * @param ptr_str_pinconfig Pointer to the pin configuration structure.
 * @param ptr_enu_pin_state Pointer to the variable where the pin state will be stored.
 * @return dio_enu_return_state_t The return state of the function:
 *         - DIO_OK: The pin state was read successfully.
 *         - Other possible return states indicating an error.
 */
dio_enu_return_state_t dio_read_pin(dio_str_pin_Config_t *ptr_str_pinconfig, dio_enu_pin_state_t *ptr_enu_pin_state)
{
	dio_enu_return_state_t return_value = DIO_OK;
	uint32_t l_un32_gpio_base_address = 0;

	if (ptr_str_pinconfig != NULL)
	{
		switch (ptr_str_pinconfig->enu_port)
		{
		case DIO_PORTA:
			l_un32_gpio_base_address = DIO_PORTA_APB;
			break;
		case DIO_PORTB:
			l_un32_gpio_base_address = DIO_PORTB_APB;
			break;
		case DIO_PORTC:
			l_un32_gpio_base_address = DIO_PORTC_APB;
			break;
		case DIO_PORTD:
			l_un32_gpio_base_address = DIO_PORTD_APB;
			break;
		case DIO_PORTE:
			l_un32_gpio_base_address = DIO_PORTE_APB;
			break;
		case DIO_PORTF:
			l_un32_gpio_base_address = DIO_PORTF_APB;
			break;
		default:
			// Handle the case when an invalid port is provided
			// You can add appropriate error handling code here if needed
			break;
		}

		*ptr_enu_pin_state = (HWREG32(l_un32_gpio_base_address + GPIODATA + (1 << (ptr_str_pinconfig->enu_pin + 2))) >> ptr_str_pinconfig->enu_pin);
	}
	else
	{
		return_value = DIO_NULL_PTR;
	}

	return return_value;
}
