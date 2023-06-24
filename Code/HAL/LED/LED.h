#ifndef LED_H
#define	LED_H


/* section : includes*/
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"


/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/
typedef enum {
    LED_OFF=0,
    LED_ON
}led_enu_status_t;

typedef struct{
    dio_enu_portx_t port_name;
    dio_enu_pinx_t pin;
    led_enu_status_t led_status;
}led_str_led_config_t;

typedef enum{
    LED_NOT_OK=0,
    LED_OK,
    LED_NULL_PTR
}led_enu_return_state_t;
/* section : Function Declaration*/
led_enu_return_state_t led_initialization(led_str_led_config_t *ptr_str_led_config);
led_enu_return_state_t led_turn_on(led_str_led_config_t *ptr_str_led_config);
led_enu_return_state_t led_turn_off(led_str_led_config_t *ptr_str_led_config);
led_enu_return_state_t led_toggle(led_str_led_config_t *ptr_str_led_config);

#endif
