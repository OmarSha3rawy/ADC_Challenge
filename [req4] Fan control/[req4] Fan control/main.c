/*
 * ADC_switch.c
 *
 * Created: 11/7/2019 4:30:36 PM
 * Author : omara
 */ 

#include <avr/io.h>
#include "TIMER.h"
#include "ADC.h"

static void fan_control(uint16 temp);


int main(void)
{
	LCD_init();
	TIMER_init(TIMER0);
	TIMER_start();
	ADC_set_callback(fan_control);
	ADC_init(&ADC_cfg);
	//LCD_clearScreen();
	//LCD_displayStringRowColumn(0,0,"temp= ");
	//ADC_set_callback(fan_control);
	
    while (1) 
    {
		
    }
}

static void fan_control(uint16 temp)
{
	sint8 temp_cel = temp / 4;
	uint8 PWM_duty = 50 + 5 * (temp_cel-37);
	
	//LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,"temp = ");
	//LCD_displayString("temp = ");
	LCD_intgerToString(temp_cel);
	LCD_displayStringRowColumn(1, 0,"duty cycle = ");
	LCD_intgerToString(PWM_duty);	
}