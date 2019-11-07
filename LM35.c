/*
 * LM35.c
 *
 * Created: 11/7/2019 2:17:35 PM
 *  Author: omara
 */ 

#include "LM35.h"



#define SENSOR_CHANNEL 0
#define Vref 2.56f
#define LM35_STEP 10.0f
#define ADC_STEP 2.5 //(Vref * 1000.0f / 1024.0f)


float LM35_read_celsius(void)
{ 
	return ADC_read(SENSOR_CHANNEL) * (ADC_STEP/LM35_STEP);
}
