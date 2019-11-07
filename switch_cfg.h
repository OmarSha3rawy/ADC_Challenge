/*
 * switch_cfg.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: COMPUTER SHOW
 */

#ifndef SWITCH_CFG_H_
#define SWITCH_CFG_H_

#include"registers.h"
#include"stdtypes.h"
#define NULL ((void*)0)

typedef enum{
	ZERO,ONE,TWO,NUM_OF_EXTERNAL_INTERRUPTS
}AVAILBLE_EXT_INTERRUPTS;

typedef enum{
	SWITCH_OK,SWITCH_NOK,SWITCH_ALREADY_INIT,SWITCH_NON_INIT,SWITCH_DISABLED
}SWITCH_STD_RETURN;

#define OFF (uint8)0
#define ON  (uint8)1

#define MAX_NUM_EXT_INT (uint8)3








#endif /* SWITCH_CFG_H_ */
