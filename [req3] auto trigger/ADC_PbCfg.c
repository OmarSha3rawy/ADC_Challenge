/*
 * ADC_PbCfg.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Mohammed Nassar
 */


#include "ADC_PbCfg.h"

//ADC_cfg_t ADC = {reference_selection,REF,ADJUST,auto_trigger,TRIGGER SOURCE,ADC_prescaler,interrupt};
const ADC_cfg_t ADC_cfg = {INTERNAL,5,RIGHT_ADJUST,AUTO_TRIGGER_EN,TIMER0_OVF,ADPS_64,INTERRUPT};

