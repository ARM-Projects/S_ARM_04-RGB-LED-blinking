#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#include "../../STD_LIBRARIES/STD_TYPES.h"

#define STK_CTRL																(*((volatile uint32_t*)0xE000E010))

#define STK_ENABLE															0
#define STK_TICK_INT														1
#define STK_CLKSOURCE														2
#define STK_COUNTFLAG														16


#define STK_LOAD																(*((volatile uint32_t*)0xE000E014))	
#define STK_VAL																	(*((volatile uint32_t*)0xE000E018))
#define STK_CALIB																(*((volatile uint32_t*)0xE000E01C))


#endif