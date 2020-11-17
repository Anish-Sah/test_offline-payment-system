# define F_CPU 16000000UL // clock speed is 16MHz

#include<avr/io.h>        // AVR header
#include<util/delay.h>    // delay header

#include "lcd.h"



//******************LCD PROGRAM STARTS*********************//
/*

#define LCD_DATA PORTB          // port B is selected as LCD data port

#define ctrl PORTD              //  port D is selected as LCD command port

#define en PD7                  // enable signal is connected to port D pin 7

#define rw PD6                  // read/write signal is connected to port D pin 6

#define rs PD5                  // register select signal is connected to port D pin 5
*/



int main(void)

{

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
	_delay_ms(100);
	
	//Keypad
	 
	
	
	return 0;
	
}
