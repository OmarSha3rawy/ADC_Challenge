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
	uint8 temp = 0;
    /* Replace with your application code */
    while (1) 
    {
		LCD_clearScreen();
		temp = (uint8)LM35_read_celsius();
		LCD_displayString("Temp = ");
		LCD_intgerToString(temp);
    }
}

