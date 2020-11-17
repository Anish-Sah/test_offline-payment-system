#define  F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "Keypad.h"

//int Balance=0;
char key[5]={0,0,0,0,0};
//int InputAmt=0;
uint8_t i=0;

void DisplayBalance();
void AskAmount();
void DisplayMsg();

ISR(INT1_vect)
{
	AskAmount();
	do
	{
		KeypadInit();
		do
		{
			key[i]= GetKey();
		} while (key[i]=='!');
		LCD_write(key[i]);
		i++;
	}while(key[i-1]!=' ');
	//InputAmt = InputAmt*10 +(key[i-1]+48);
	//Balance += InputAmt;
	DisplayMsg();
	DisplayBalance();
}

int main(void)
{ 
	//Setting for LCD
	DDRB=0xFF;              // set LCD data port as output
	DDRD=0xE4;              // set LCD signals (RS, RW, E) as out put
	
	//Setting interrupt 
	PORTD |=1<<PIND3;
	GICR |= 1<<INT1;
	sei();
	
	//LCD initialization
	init_LCD();             // initialize LCD
	_delay_ms(10);         // delay of 10 Milli seconds
	LCD_cmd(0x0C);			//display on, cursor off
	_delay_ms(10);
	while(1)
	{
	
	}
	return 0;
}


void AskAmount()
{
	LCD_cmd(0x01);			//Clear Display
	_delay_ms(10);
	LCD_Write_String("ENTER  AMOUNT:");
	_delay_ms(10);
	LCD_cmd(0xC0);			// move cursor to the beginning of the 2nd row
	_delay_ms(10);
	LCD_cmd(0x0E);			//display on, cursor on
	_delay_ms(10);
}

void DisplayMsg()
{
	LCD_cmd(0x01);				//Clear Screen
	_delay_ms(10);
	LCD_Write_String("Processing...");
	_delay_ms(1000);
	LCD_cmd(0x01);				//Clear Screen
	_delay_ms(10);
	LCD_Write_String("Transaction");
	LCD_cmd(0xC0);			// move cursor to the beginning of the 2nd row
	_delay_ms(10);
	LCD_Write_String("Complete.");
	_delay_ms(1000);
}

void DisplayBalance()
{
	LCD_cmd(0x01);
	_delay_ms(10);
	LCD_Write_String("Current Balance:");
	_delay_ms(10);
	LCD_cmd(0xC0);			// move cursor to the beginning of the 2nd row
	_delay_ms(10);
	for(i=0;i<5;i++)
		{
			LCD_write(key[i]);
		}
}