/*
 * switch_Pbcfg.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: COMPUTER SHOW
 */

#ifndef SWITCH_PBCFG_H_
#define SWITCH_PBCFG_H_

#include"switch_cfg.h"

typedef enum {
	EXT_INT0,EXT_INT1,EXT_INT2,
}INTERRUPT_TYPE;

typedef  enum {
	FALLING,RISING,
}SELECTED_EDGE;



typedef struct{
	INTERRUPT_TYPE interrupt;
	SELECTED_EDGE  edge;
	uint8 enable;
}SWITCH_CNFG_ST;

extern SWITCH_CNFG_ST switch_Configurations[MAX_NUM_EXT_INT];

#endif /* SWITCH_PBCFG_H_ */
