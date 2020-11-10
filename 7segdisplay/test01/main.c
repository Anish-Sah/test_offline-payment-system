#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>


#include "LedDisplay.h"

char flag;
short int balance = 4999;

char check_pw()
{
	  short int tran_amt;
	  char msg[10]="1234921001";
	  //char Card_ID[10] = "test001";                   //needs to be changed
	  //decoding msg
	  
	  if(msg[0]=='1'&& msg[1]=='2'&& msg[2]=='3' && msg[3]=='4')     //1st 2nd 3rd and 4th digit act as password
	  {
		  tran_amt= (msg[6]-48)*100+(msg[7]-48)*10+(msg[8]-48);
		  if(balance>tran_amt)
		  {
			  if(msg[9]=='1')                           //1: Recharge and 0: pay in the 10th digit
				 balance+=tran_amt;
			  else
				 balance-=tran_amt;
			 flag ='1';
		  }
	  }
	 else
	    flag ='0';
return flag;	
}


int main()
{	
	uint8_t counter=0;
	TCCR1B |= 1<<CS10;	 
	flag = check_pw();
	while(counter<60)
	{
		while(TCNT1<60000)
		{
			counter++;
			if(flag=='1')
			led_display_succ();
			else
			led_display_fail();
		}
		TCNT1 =0;
		counter ++;
	}
	
	while(1)
	{
		led_display(balance); 		
	}
	return 0;
	
}

