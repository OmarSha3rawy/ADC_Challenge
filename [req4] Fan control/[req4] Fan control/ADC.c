/*
 * ADC.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Mohammed Nassar
 */

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "ADC.h"

/*  AVAILABITITY  */
#define AVAILABLE     1
#define NOT_AVAILABLE 0

/* REQUEST */
#define REQUESTED     1
#define NOT_REQUESTED 0

static volatile uint16_func_ptr g_ADC_consumer_ptr = NULL;
static void ADC_start_conversion(void);


ADC_error_t ADC_init(ADC_cfgPtr_t ADC_cfg)
{
	ADC_error_t retval = ADC_OK ;

	/* REFERENCE SELECTION */
	switch(ADC_cfg->reference_selection)
	{
	case AREF:  ADMUX &= ~( (1<<REFS1) | (1<<REFS0) ) ; // AREF
	break;
	case AVCC : ADMUX &= ~(1<<REFS1);
		        ADMUX |= (1<<REFS0);          // AVCC
	break;
	case INTERNAL : ADMUX |= ( (1<<REFS1) | (1<<REFS0) ) ; // INTERNAL
	break;
	default: retval = ADC_INVALID_CFG ;
	break;
	}

	/* ADJUST RESULT   */
	switch(ADC_cfg->adjust)
	{
	case LEFT_ADJUST :ADMUX |=  (1<<ADLAR) ; // LEFT_ADJUST
	break;
	case RIGHT_ADJUST : ADMUX &= ~(1<<ADLAR);  // RIGHT_ADJUST
	break;
	default: retval = ADC_INVALID_CFG ;
	break;
	}

	ADC_set_Channel(0);

	ADCSRA |=(1<<ADEN);   /******** ADC ENABLE ********/

	/* AUTO_TRIGGER_EN */
	switch(ADC_cfg->auto_trigger)
	{
	case AUTO_TRIGGER_DIS :  ADCSRA &= ~(1<<ADATE);//AUTO TRIGGER DISABLE
	break;
	case AUTO_TRIGGER_EN : ADCSRA |= (1<<ADATE); //AUTO TRIGGER ENABLE
	break;
	default: retval = ADC_INVALID_CFG ;
	break;
	}

/*  TRIGGER SOURCE   */
	switch(ADC_cfg->trigger_source)
	{
	case FREE_RUNNING :  SFIOR &= ~( (1<<ADTS2) | (1<<ADTS1)| (1<<ADTS0) );
	break;
	case ANALOG_COMPARATOR : SFIOR &= ~( (1<<ADTS2) | (1<<ADTS1));
	                         SFIOR |=(1<<ADTS0);
	break;
	case EX_INTERRUPT :SFIOR &= ~( (1<<ADTS2) | (1<<ADTS0) );
	                   SFIOR |=(1<<ADTS1);
	break;
	case TIMER0_CMP :  SFIOR &= ~(1<<ADTS2);
		               SFIOR |=( (1<<ADTS1) |(1<<ADTS0) ) ;
	break;
	case TIMER0_OVF :  SFIOR &= ~( (1<<ADTS1) | (1<<ADTS0) );
	                   SFIOR |=(1<<ADTS2);
	break;
	case TIMER1B_CMP : SFIOR &= ~(1<<ADTS1);
                       SFIOR |=( (1<<ADTS2) |(1<<ADTS0) ) ;
	break;
	case TIMER1B_OVF : SFIOR &= ~(1<<ADTS0);
                       SFIOR |=( (1<<ADTS2) |(1<<ADTS1) ) ;
	break;
	case TIMER1_ICU :  SFIOR |=( (1<<ADTS2) | (1<<ADTS1) |(1<<ADTS0) ) ;
	break;
	default: retval = ADC_INVALID_CFG ;
	break;
	}

	/*  ADC PRESCALER   */
	switch(ADC_cfg->ADC_prescaler)
	{
	case ADPS_2 : ADCSRA &= ~( (1<<ADPS2) | (1<<ADPS1)| (1<<ADPS0) );
	break;
	case ADPS_4 : ADCSRA &= ~( (1<<ADPS2) | (1<<ADPS0) );
	              ADCSRA |=(1<<ADPS1);
	break;
	case ADPS_8 : ADCSRA &= ~(1<<ADPS2);
	              ADCSRA |=( (1<<ADPS1) | (1<<ADPS0) ) ;
	break;
	case ADPS_16 : ADCSRA &= ~( (1<<ADPS1) | (1<<ADPS0) );
                   ADCSRA |=(1<<ADPS2);
	break;
	case ADPS_32 : ADCSRA &= ~(1<<ADPS1);
                   ADCSRA |=( (1<<ADPS2) |(1<<ADPS0) ) ;
	break;
	case ADPS_64 : ADCSRA &= ~(1<<ADPS0);
                   ADCSRA |=( (1<<ADPS2) |(1<<ADPS1) ) ;
	break;
	case ADPS_128 : ADCSRA |=( (1<<ADPS2) | (1<<ADPS1) |(1<<ADPS0) ) ;
	break;
	default: retval = ADC_INVALID_CFG ;
	break;
	}

/* INTERRUPT */
	switch(ADC_cfg->interrupt)
	{
	case  POOLING :  ADCSRA &= ~(1<<ADIE);
	break;
	case INTERRUPT :
		sei();  // Global INTERRUPT Enable
		ADCSRA |= (1<<ADIE);
		break;
	default: retval = ADC_INVALID_CFG ;
	break;
	}


	return retval;
}



ADC_error_t ADC_read(uint16 *Data)
{
	ADC_error_t retval = ADC_OK ;
	if  (ADC_cfg.auto_trigger == AUTO_TRIGGER_DIS  )
	{

	if  (ADC_cfg.interrupt== POOLING  )
	{
		ADC_start_conversion();

		while ( BIT_IS_CLEAR(ADCSRA,ADIF) ){  }    //POOLING  D
		ADCSRA |= (1<<ADIF);
		switch(ADC_cfg.adjust)
		{
		case LEFT_ADJUST : *Data = ( ( *Data & 0x0000) | ( (uint16) ADCH << 2 ) ) ;
		                   *Data |= ( (uint16) (ADCL & 0xC0) >> 6 ) ; // LEFT_ADJUST
		break;
		case RIGHT_ADJUST : *Data = ADCL  ;
                            *Data |= ( (uint16)ADCH  << 8 ) ;// RIGHT_ADJUST
		break;
		}

	}
	else if  (ADC_cfg.interrupt == INTERRUPT  )
	{
		ADC_start_conversion();
	}
	}

	else if (ADC_cfg.auto_trigger == AUTO_TRIGGER_EN  )
	{









	}

	return retval;
}


ADC_error_t ADC_set_Channel(uint8 Channel)
{
	ADC_error_t retval = ADC_OK ;

	Channel= ( 0x1F & Channel );
		ADMUX  &= 0xE0 ;
	    ADMUX |= Channel ;

	return retval;
}

void ADC_start_conversion(void)
{
 ADCSRA |= (1<<ADSC);
}

ADC_error_t ADC_set_callback(uint16_func_ptr app_ptr)
{
	ADC_error_t retval = ADC_OK ;
	g_ADC_consumer_ptr = app_ptr;
	return retval;
}

ISR(ADC_vect)
{
if (g_ADC_consumer_ptr != NULL)
	{
	uint16 Data=0;
	switch(ADC_cfg.adjust)
	{
	case LEFT_ADJUST : Data = ( (Data & 0x0000) | ( (uint16) ADCH << 2 ) ) ;
			           Data |= ( (uint16) (ADCL & 0xC0) >> 6 ) ; // LEFT_ADJUST
	break;
	case RIGHT_ADJUST : Data = ADCL  ;
	                    Data |= ( (uint16)ADCH  << 8 ) ;// RIGHT_ADJUST
	break;
	}
	g_ADC_consumer_ptr(ADC);
	}
}











