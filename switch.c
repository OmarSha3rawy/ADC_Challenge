/*
 * switch.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: COMPUTER SHOW
 */


#include"switch.h"

static volatile void (*ext_int_zero_g_ptr)(void);
static volatile void (*ext_int_one_g_ptr)(void);
static volatile void (*ext_int_two_g_ptr)(void);

void set_ext_int_zero_CBK(void(*ptr)(void))
{
	ext_int_zero_g_ptr = ptr;
}
void set_ext_int_one_CBK(void(*ptr)(void))
{
	ext_int_one_g_ptr = ptr;
}
void set_ext_int_two_CBK(void(*ptr)(void))
{
	ext_int_two_g_ptr = ptr;
}
ISR(INT0_vect)
{
	if(ext_int_zero_g_ptr != NULL)
	{
		(*ext_int_zero_g_ptr)();
	}
}
ISR(INT1_vect)
{
	if(ext_int_one_g_ptr != NULL)
	{
		(*ext_int_one_g_ptr)();
	}
}
ISR(INT2_vect)
{
	if(ext_int_two_g_ptr != NULL)
	{
		(*ext_int_two_g_ptr)();
	}
}
SWITCH_STD_RETURN external_interrupt_init(void)
{
	SWITCH_STD_RETURN retVal = SWITCH_OK;
	uint8 loop_iterator = 0;
	if(NUM_OF_EXTERNAL_INTERRUPTS > MAX_NUM_EXT_INT)
	{
		retVal = SWITCH_NOK;
	}
	else
	{
		for(loop_iterator=0;loop_iterator<MAX_NUM_EXT_INT;loop_iterator++)
		{
			if(switch_Configurations[loop_iterator].enable == ON)
			{
				if(switch_Configurations[loop_iterator].interrupt == EXT_INT0)
				{
					if(switch_Configurations[loop_iterator].edge == RISING)
					{
						SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
						DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
						GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
						MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge
						SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
					}
					else if(switch_Configurations[loop_iterator].edge == FALLING)
					{
						SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
						DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
						PORTD |= (1<<PD2);
						GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
						MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge
						SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
					}
					else
					{
						retVal = SWITCH_NOK;
					}
				}
				else if(switch_Configurations[loop_iterator].interrupt == EXT_INT1)
				{
					if(switch_Configurations[loop_iterator].edge == FALLING)
					{
						SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
						DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
						PORTD |= (1<<PD3);     // Enable the internal pull up resistor at PD3 pin
						GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
						// Trigger INT1 with the falling edge
						MCUCR |= (1<<ISC11);
						MCUCR &= ~(1<<ISC10);
						SREG  |= (1<<7);       // Enable interrupts by setting I-bit

					}
					else if(switch_Configurations[loop_iterator].edge == RISING)
					{
						SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
						DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
						GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
						// Trigger INT1 with the falling edge
						MCUCR |= (1<<ISC11);
						MCUCR &= ~(1<<ISC10);
						SREG  |= (1<<7);       // Enable interrupts by setting I-bit

					}
					else
					{
						retVal = SWITCH_NOK;
					}
				}
				else if(switch_Configurations[loop_iterator].interrupt == EXT_INT2)
				{
					if(switch_Configurations[loop_iterator].edge == FALLING)
					{
						SREG   &= ~(1<<7);      // Disable interrupts by clearing I-bit
						DDRB   &= (~(1<<PB2));   // Configure INT2/PB2 as input pin
						GICR   |= (1<<INT2);	// Enable external interrupt pin INT2
						MCUCSR |= (1<<ISC2);    // Trigger INT2 with the raising edge
						SREG   |= (1<<7);       // Enable interrupts by setting I-bit
					}
					else if(switch_Configurations[loop_iterator].edge == RISING)
					{
						SREG   &= ~(1<<7);      // Disable interrupts by clearing I-bit
						DDRB   &= (~(1<<PB2));   // Configure INT2/PB2 as input pin
						GICR   |= (1<<INT2);	// Enable external interrupt pin INT2
						MCUCSR |= (1<<ISC2);    // Trigger INT2 with the raising edge
						SREG   |= (1<<7);       // Enable interrupts by setting I-bit
					}
					else
					{
						retVal = SWITCH_NOK;
					}
				}
				else
				{
					retVal = SWITCH_NOK;
				}
			}
			else if(switch_Configurations[loop_iterator].enable == OFF)
			{
				retVal = SWITCH_DISABLED;
			}
		}

	}
	return retVal;
}
