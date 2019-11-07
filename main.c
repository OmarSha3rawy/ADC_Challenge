/*
 * ADC_CHALLENGE.c
 *
 * Created: 11/7/2019 2:15:02 PM
 * Author : omara
 */ 

#include <avr/io.h>
#include "LM35.h"
#include "lcd.h"

int main(void)

{
	LCD_init();
	ADC_init();
	uint8 temp = 0;
	LCD_displayString("Temp = ");
    /* Replace with your application code */
    while (1) 
    {
		//LCD_clearScreen();
		temp = (uint8)LM35_read_celsius() - 1; // the float to int conversion adaption

		LCD_goToRowColumn(0, 7);
		LCD_intgerToString(temp);
    }
}

