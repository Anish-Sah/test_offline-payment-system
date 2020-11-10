#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int digit[18]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92 , 0x82, 0xF8, 0x80, 0x90, 0x88, 0xC6, 0x8E, 0xCF,0xC7, 0x92, 0xC1, 0x7F};
int	digit_place[4]={0x01,0x02,0x04,0x08};

void initialize()
{
	DDRD=0x0F;
	DDRC=0xFF;
	PORTC = 0xFF;
}

void led_display(int num)
{
	initialize();				
	short int digit1, digit2, digit3, digit4;
	digit4 = num%10;
	digit3 = (num%100)/10;
	digit2 = (num%1000)/100;
	digit1 = num/1000;
	PORTD = digit_place[0];
	PORTC = digit[digit1];
	_delay_ms(10);
	PORTD = digit_place[1];
	PORTC = digit[digit2];
	_delay_ms(10);
	PORTD = digit_place[2];
	PORTC = digit[digit3];
	_delay_ms(10);
	PORTD = digit_place[3];
	PORTC = digit[digit4];
	_delay_ms(10);
}

void led_display_succ()
{
	initialize();
	PORTD = digit_place[0];
	PORTC = digit[15];
	_delay_ms(10);
	PORTD = digit_place[1];
	PORTC = digit[16];
	_delay_ms(10);
	PORTD = digit_place[2];
	PORTC = digit[11];
	_delay_ms(10);
	PORTD = digit_place[3];
	PORTC = digit[11];
	_delay_ms(10);
	PORTD = digit_place[3];
	PORTC = digit[17];
	_delay_ms(10);	
}

void led_display_fail()
{
	initialize();
	PORTD = digit_place[0];
	PORTC = digit[12];
	_delay_ms(10);
	PORTD = digit_place[1];
	PORTC = digit[10];
	_delay_ms(10);
	PORTD = digit_place[2];
	PORTC = digit[13];
	_delay_ms(10);
	PORTD = digit_place[3];
	PORTC = digit[14];
	_delay_ms(10);
		
}

