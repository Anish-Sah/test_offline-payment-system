#define  F_CPU 8000000UL

#define KeypadDirectionRegister		DDRC
#define KeypadPortControl			PORTC
#define KeypadPortValue				PINC
#define LcdDDR						DDRB
#define LcdData						PORTB
#define LcdCmdDDR					DDRD
#define	LcdCmdPort					PORTD


#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "Keypad.h"




int main(void)

{
	char key;	
	DDRB=0xFF;              // set LCD data port as output
	DDRD=0xE0;              // set LCD signals (RS, RW, E) as out put

	init_LCD();             // initialize LCD
	_delay_ms(10);         // delay of 10 Milli seconds
	
	LCD_cmd(0x0C);			//display on, cursor off
	_delay_ms(10);
	//LCD display asking for amount
	
	LCD_Write_String("ENTER  AMOUNT:  ");
	_delay_ms(10);
	LCD_cmd(0xC0);			// move cursor to the beginning of the 2nd row
	_delay_ms(10);
	LCD_cmd(0x0E);			//display on, cursor on
	_delay_ms(10);
		
	Init();
	while(1)
	{
		key= GetKey();				//Getting key by polling method
		if(key!='!')
			LCD_write(key);
	}
	
	return 0;
}


