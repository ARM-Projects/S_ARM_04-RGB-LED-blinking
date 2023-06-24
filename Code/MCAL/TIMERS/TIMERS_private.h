#ifndef TIMERS_PRIVATE_H
#define TIMERS_PRIVATE_H

#include "../../STD_LIBRARIES/STD_TYPES.h"

#define RCGCTIMER																*((volatile uint32_t*)0x400FE604)
#define RCGCWTIMER															*((volatile uint32_t*)0x400FE65C)



#define TIMER_0																  0x40030000
#define TIMER_1 																0x40031000
#define TIMER_2																  0x40032000
#define TIMER_3																  0x40033000
#define TIMER_4																  0x40034000
#define TIMER_5																 	0x40035000


#define WIDE_TIMER_0														0x40036000
#define WIDE_TIMER_1														0x40037000
#define WIDE_TIMER_2														0x4004C000
#define WIDE_TIMER_3														0x4004D000
#define WIDE_TIMER_4														0x4004E000
#define WIDE_TIMER_5														0x4004F000

#define GPTMCTL																	0x00C		
#define	TAEN																		0
#define	TASTALL																	1
#define	TAEVENT																	2
#define	RTCEN																		4
#define TAOTE																		5
#define TAPWML																	6
#define	TBEN																		8
#define	TBSTALL																	9
#define	TBEVENT																	10
#define TBOTE																		13
#define TBPWML																	14


#define GPTMCFG																	0x000


#define GPTMTAMR																0x004
#define TAMR																		0
#define TACMR																		2
#define TAAMS																		3
#define TACDIR																	4
#define TAMIE																		5
#define TAWOT																		6
#define TASNAPS																	7
#define TAILD																		8
#define TAPWMIE																	9
#define TAMRSU																	10
#define TAPLO																		11




#define GPTMTBMR																0x008
#define TBMR																		0
#define TBCMR																		2
#define TBAMS																		3
#define TBCDIR																	4
#define TBMIE																		5
#define TBWOT																		6
#define TBSNAPS																	7
#define TBILD																		8
#define TBPWMIE																	9
#define TBMRSU																	10
#define TBPLO																		11



#define GPTMTAILR																0x028

#define GPTMTBILR																0x02C

#define GPTMIMR																	0x018
#define TAMIM																	  4 
#define RTCIM 																	3
#define CAEIM 																	2
#define CAMIM 																	1
#define TATOIM 																	0


#define TBMIM																	  11 
#define CBEIM 																	10
#define CBMIM 																	9
#define TBTOIM 																	8
#define WUECINT 																16 //todo


#define GPTMICR																	0x024 
#define TAMCINT  																4 
#define RTCCINT  																3 
#define CAECINT  																2 
#define CAMCINT  																1 
#define TATOCINT 																0

#define TBMCINT  																11 
#define CBECINT  																10
#define CBMCINT  																9 
#define TBTOCINT 																8

#define GPTMTAPR																0x038

#define GPTMMIS																	0x020
#define TATOMIS																	0


#endif