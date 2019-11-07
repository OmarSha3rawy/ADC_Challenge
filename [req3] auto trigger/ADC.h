/*
 * ADC.h
 *
 *  Created on: Nov 7, 2019
 *      Author: Mohammed Nassar
 */

#ifndef ADC_H_
#define ADC_H_

#include "ADC_Cfg.h"

typedef struct
{
	uint8 reference_selection;
	uint8 REF;
	uint8 adjust;
	uint8 auto_trigger;
	uint8 trigger_source;
	uint8 ADC_prescaler;
	uint8 interrupt;
} ADC_cfg_t ;

#include "ADC_PbCfg.h"

typedef const ADC_cfg_t* ADC_cfgPtr_t;

typedef uint8 ADC_error_t;
#define ADC_OK           0
#define ADC_INVALID_CFG   1

extern ADC_error_t ADC_init(ADC_cfgPtr_t);
extern ADC_error_t ADC_set_Channel(uint8 Channel);
extern ADC_error_t ADC_read(uint16*);
extern ADC_error_t ADC_set_callback(uint16_func_ptr app_ptr);

#endif /* ADC_H_ */
