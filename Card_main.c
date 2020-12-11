#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "Display7Seg.h"

uint16_t balance;
//short int balance = 99;
char msg[10]="1234921001";					//Decrypted Msg
char feedback;

char check_pw()
{
	short int tran_amt;
	if(msg[0]=='1'&& msg[1]=='2'&& msg[2]=='3' && msg[3]=='4')     //1st 2nd 3rd and 4th digit act as password
	{
		tran_amt= (msg[6]-48)*100+(msg[7]-48)*10+(msg[8]-48);		//Calculating Transaction amount
		if(msg[9]=='1')												 //1: Recharge in the 10th digit
			{
				balance+=tran_amt;
				eeprom_update_word((uint16_t *) 20, balance);	//writing the balance to eeprom, in the memory address 20 in EEPROM
				return 's';											//s Feedback signal: Recharge Successful
			}
		else 
			{
				if(tran_amt<balance)					//Payment if balance is greater than Transaction amount
					{
						balance-=tran_amt;
						eeprom_update_word((uint16_t *) 20, balance);	//writing the balance to eeprom, in the memory address 20 in EEPROM
						return 's';						//s signals payment successful
					}
				else
					return 'i';							//i signals insufficient balance
			}					
	}
	else
		return '0';										//Authentication Error
}

ISR(INT1_vect)								//in place of INT1_ vect -> RXCIE for Receive pin interrupt
{
	//Receive Encrypted Msg
	//Decrypt the Msg
	//Authentication
	//Check for sufficient amount
	//Increase or decrease amount
	feedback= check_pw();
	//Send Feedback Signal
	
	//Display Transaction success or failure for 5 Seconds
	uint8_t counter=0;
	TCCR1B |= 1<<CS10;
	while(counter<60)
	{
		while(TCNT1<60000)
		{
			counter++;
			if(feedback== 's')	led_display_succ();
			if(feedback== 'i' || feedback == '0')	led_display_fail();
		}
		TCNT1 =0;
		counter ++;
	}
}


int main()
{
	//Setting interrupt
	DDRD = (1<<PIND3);						//Pind3 is for INT1 
	PORTD |=1<<PIND3;
	GICR |= 1<<INT1;
	sei();
	//Initial initialization of the balance
	char check= eeprom_read_word((char *) 10);
	if(check != '@')	eeprom_update_word((uint16_t *) 20, 99);	//writing the balance to eeprom, in the memory address 20 in EEPROM
	eeprom_update_word((char*)10,'@');
	//getting balance from EEPROM
	balance = eeprom_read_word((uint16_t *) 20);
	
	while(1)
	{
		led_display(balance);
		//Jump to ISR for transaction when Receiving interrupt is triggered 
	}
	return 0;
	
}

