#ifndef SYS_CONTROL_INTERFACE_H
#define	SYS_CONTROL_INTERFACE_H


#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"

typedef enum{
	SYS_CONTROL_MOSC=0,
	SYS_CONTROL_PIOSC=1,
	SYS_CONTROL_PIOSC_4=2,
	SYS_CONTROL_LFIOSC=3
	
}sys_control_enu_OSCSRC_t;



typedef struct{
	uint8_t prescaller :4;
	sys_control_enu_OSCSRC_t  enu_OSCSRC;
}sys_control_str_config_t;

;

void sys_control_set_clock_system(sys_control_str_config_t *ptr_str_sys_control_config);
#endif