#include "Button.h"
/**
 * @brief Initializes a button based on the provided configuration.
 *
 * This function initializes a button based on the configuration specified by the pointer `ptr_str_btn_config`.
 * The function checks if the pointer is NULL and returns `BTN_NULL_PTR` if true.
 * If the pointer is not NULL, the function initializes the button's corresponding pin based on the configuration.
 * The pin is configured as an input with either a pull-up or pull-down resistor based on the `button_active` field in the configuration.
 * The function utilizes the `dio_init_pin()` function to initialize the pin.
 *
 * @param ptr_str_btn_config Pointer to the button configuration structure.
 * @return brn_enu_return_state_t Status of the function, which can be:
 *         - BTN_OK: The function executed successfully.
 *         - BTN_NULL_PTR: The provided pointer is NULL.
 */
brn_enu_return_state_t button_initialization(const button_str_btn_config_t *ptr_str_btn_config)
{
    brn_enu_return_state_t ret = BTN_OK; // Initialize the return status to BTN_OK

    if (ptr_str_btn_config == NULL)
    {
        ret = BTN_NULL_PTR; // Return BTN_NULL_PTR if the provided pointer is NULL
    }
    else
    {
        dio_str_pin_Config_t temp = {
            .enu_port = ptr_str_btn_config->port_name,
            .enu_pin = ptr_str_btn_config->pin,
            .enu_pin_mode = DIO_PIN_INPUT,
            .un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP};

        if (ptr_str_btn_config->button_active == BUTTON_ACTIVE_LOW)
        {
            temp.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP; // Configure as input with pull-up resistor if button active low
        }
        else
        {
            temp.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_DOWN; // Configure as input with pull-down resistor if button active high
        }

        dio_init_pin(&temp); // Initialize the pin based on the configuration
    }

    return ret; // Return the status of the function
}

/**
 * @brief Reads the state of a button based on the provided configuration.
 *
 * This function reads the state of a button based on the configuration specified by the pointer `ptr_str_btn_config`.
 * The function also stores the returned state in the pointer `ptr_enu_btn_state`.
 * The function checks if either `ptr_str_btn_config` or `ptr_enu_btn_state` is NULL and returns `BTN_NOT_OK` if true.
 * If both pointers are valid, the function initializes the button's corresponding pin based on the configuration.
 * The pin is configured as an input with either a pull-up or pull-down resistor based on the `button_active` field in the configuration.
 * The function utilizes the `dio_read_pin()` function to read the pin state and compares it with the button active mode to determine the button state.
 * The determined button state is stored in the `ptr_enu_btn_state` pointer.
 *
 * @param ptr_str_btn_config Pointer to the button configuration structure.
 * @param ptr_enu_btn_state Pointer to store the returned button state.
 * @return brn_enu_return_state_t Status of the function, which can be:
 *         - BTN_OK: The function executed successfully.
 *         - BTN_NOT_OK: One or both of the provided pointers is NULL.
 */
brn_enu_return_state_t button_read_state(button_str_btn_config_t *ptr_str_btn_config, btn_enu_btn_state_t *ptr_enu_btn_state)
{
    brn_enu_return_state_t ret = BTN_OK; // Initialize the return status to BTN_OK
    dio_enu_pin_state_t l_enu_pin_state;

    if (ptr_str_btn_config == NULL || ptr_enu_btn_state == NULL)
    {
        ret = BTN_NOT_OK; // Return BTN_NOT_OK if either pointer is NULL
    }
    else
    {
        dio_str_pin_Config_t temp = {
            .enu_port = ptr_str_btn_config->port_name,
            .enu_pin = ptr_str_btn_config->pin,
            .enu_pin_mode = DIO_PIN_INPUT,
            .un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP};

        if (ptr_str_btn_config->button_active == BUTTON_ACTIVE_LOW)
        {
            temp.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP; // Configure as input with pull-up resistor if button active low
        }
        else
        {
            temp.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_DOWN; // Configure as input with pull-down resistor if button active high
        }

        dio_read_pin(&temp, &l_enu_pin_state); // Read the pin state

        if (((ptr_str_btn_config->button_active == BUTTON_ACTIVE_LOW) && (l_enu_pin_state == DIO_PIN_LOW_STATE)) ||
            ((ptr_str_btn_config->button_active == BUTTON_ACTIVE_HIGH) && (l_enu_pin_state == DIO_PIN_HIGH_STATE)))
        {
            *ptr_enu_btn_state = BUTTON_PRESSED; // Set button state as pressed if it matches the button active mode and pin state
        }
        else
        {
            *ptr_enu_btn_state = BUTTON_RELEASED; // Set button state as released otherwise
        }
    }

    return ret; // Return the status of the function
}