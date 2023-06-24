#include "LED.h"


/**
 * @brief Initializes an LED based on the provided configuration.
 *
 * This function initializes an LED based on the configuration specified by the pointer `ptr_str_led_config`.
 * The function checks if the pointer is NULL and returns `LED_NULL_PTR` if true.
 * If the pointer is not NULL, the function initializes the LED's corresponding pin based on the configuration.
 * The pin is configured as an output with the specified output current and initial pin state.
 * The function utilizes the `dio_init_pin()` function to initialize the pin.
 *
 * @param ptr_str_led_config Pointer to the LED configuration structure.
 * @return led_enu_return_state_t Status of the function, which can be:
 *         - LED_OK: The function executed successfully.
 *         - LED_NULL_PTR: The provided pointer is NULL.
 */
led_enu_return_state_t led_initialization(led_str_led_config_t *ptr_str_led_config)
{
    led_enu_return_state_t res = LED_OK; // Initialize the return status to LED_OK

    if (ptr_str_led_config == NULL)
    {
        res = LED_NULL_PTR; // Return LED_NULL_PTR if the provided pointer is NULL
    }
    else
    {
        dio_str_pin_Config_t temp = {
            .enu_port = ptr_str_led_config->port_name,
            .enu_pin = ptr_str_led_config->pin,
            .enu_pin_mode = DIO_PIN_OUTPUT,
            .un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_4MA,
            .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_HIGH_STATE};

        if (ptr_str_led_config->led_status == LED_OFF)
        {
            temp.un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE; // Set pin state as low if LED status is off
        }
        else
        {
            temp.un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_HIGH_STATE; // Set pin state as high otherwise
        }

        dio_init_pin(&temp); // Initialize the pin based on the configuration
    }

    return res; // Return the status of the function
}

/**
 * @brief Turns on an LED based on the provided configuration.
 *
 * This function turns on an LED based on the configuration specified by the pointer `ptr_str_led_config`.
 * The function checks if the pointer is NULL and returns `LED_NULL_PTR` if true.
 * If the pointer is not NULL, the function initializes the LED's corresponding pin based on the configuration.
 * The pin is configured as an output with the specified output current and initial pin state.
 * The function then utilizes the `dio_set_pin()` function to set the pin state to high, effectively turning on the LED.
 *
 * @param ptr_str_led_config Pointer to the LED configuration structure.
 * @return led_enu_return_state_t Status of the function, which can be:
 *         - LED_OK: The function executed successfully.
 *         - LED_NULL_PTR: The provided pointer is NULL.
 */
led_enu_return_state_t led_turn_on(led_str_led_config_t *ptr_str_led_config)
{
    led_enu_return_state_t res = LED_OK; // Initialize the return status to LED_OK

    if (ptr_str_led_config == NULL)
    {
        res = LED_NULL_PTR; // Return LED_NULL_PTR if the provided pointer is NULL
    }
    else
    {
        dio_str_pin_Config_t temp = {
            .enu_port = ptr_str_led_config->port_name,
            .enu_pin = ptr_str_led_config->pin,
            .enu_pin_mode = DIO_PIN_OUTPUT,
            .un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_4MA,
            .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_HIGH_STATE};

        dio_set_pin(&temp, DIO_PIN_HIGH_STATE); // Set the pin state to high, turning on the LED
    }

    return res; // Return the status of the function
}

/**
 * @brief Turns off an LED based on the provided configuration.
 *
 * This function turns off an LED based on the configuration specified by the pointer `ptr_str_led_config`.
 * The function checks if the pointer is NULL and returns `LED_NULL_PTR` if true.
 * If the pointer is not NULL, the function initializes the LED's corresponding pin based on the configuration.
 * The pin is configured as an output with the specified output current and initial pin state.
 * The function then utilizes the `dio_set_pin()` function to set the pin state to low, effectively turning off the LED.
 *
 * @param ptr_str_led_config Pointer to the LED configuration structure.
 * @return led_enu_return_state_t Status of the function, which can be:
 *         - LED_OK: The function executed successfully.
 *         - LED_NULL_PTR: The provided pointer is NULL.
 */
led_enu_return_state_t led_turn_off(led_str_led_config_t *ptr_str_led_config)
{
    led_enu_return_state_t res = LED_OK; // Initialize the return status to LED_OK

    if (ptr_str_led_config == NULL)
    {
        res = LED_NULL_PTR; // Return LED_NULL_PTR if the provided pointer is NULL
    }
    else
    {
        dio_str_pin_Config_t temp = {
            .enu_port = ptr_str_led_config->port_name,
            .enu_pin = ptr_str_led_config->pin,
            .enu_pin_mode = DIO_PIN_OUTPUT,
            .un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_4MA,
            .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_HIGH_STATE};

        dio_set_pin(&temp, DIO_PIN_LOW_STATE); // Set the pin state to low, turning off the LED
    }

    return res; // Return the status of the function
}

/**
 * @brief Toggles the state of an LED based on the provided configuration.
 *
 * This function toggles the state of an LED based on the configuration specified by the pointer `ptr_str_led_config`.
 * The function checks if the pointer is NULL and returns `LED_NULL_PTR` if true.
 * If the pointer is not NULL, the function initializes the LED's corresponding pin based on the configuration.
 * The pin is configured as an output with the specified output current and initial pin state.
 * The function then utilizes the `dio_toggle_pin()` function to toggle the pin state, effectively toggling the LED state.
 *
 * @param ptr_str_led_config Pointer to the LED configuration structure.
 * @return led_enu_return_state_t Status of the function, which can be:
 *         - LED_OK: The function executed successfully.
 *         - LED_NULL_PTR: The provided pointer is NULL.
 */
led_enu_return_state_t led_toggle(led_str_led_config_t *ptr_str_led_config)
{
    led_enu_return_state_t res = LED_OK; // Initialize the return status to LED_OK

    if (ptr_str_led_config == NULL)
    {
        res = LED_NULL_PTR; // Return LED_NULL_PTR if the provided pointer is NULL
    }
    else
    {
        dio_str_pin_Config_t temp = {
            .enu_port = ptr_str_led_config->port_name,
            .enu_pin = ptr_str_led_config->pin,
            .enu_pin_mode = DIO_PIN_OUTPUT,
            .un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = DIO_PIN_4MA,
            .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_HIGH_STATE};

        dio_toggle_pin(&temp); // Toggle the pin state, effectively toggling the LED state
    }

    return res; // Return the status of the function
}

