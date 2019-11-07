/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: COMPUTER SHOW
 */


#include"DIO.h"
#include"switch.h"

#include"switch.h"

void func_CBK(void)
{
	PORTC ^= (1<<0);
}
void main(void)
{
	DDRC |= (1<<0);


	external_interrupt_init();
	//set_ext_int_zero_CBK(func_CBK);
	//set_ext_int_one_CBK(func_CBK);
	set_ext_int_two_CBK(func_CBK);
	while(1)
	{

	}
}
