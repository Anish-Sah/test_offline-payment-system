#define F_CPU 8000000UL
#include <util/delay.h>

#include "LedDisplay.h"

int main()
{	
   		   short int tran_amt;
		   short int flag=0;
		   char msg[10]="1234921000";
		   //char Card_ID[10] = "test001";                   //needs to be changed
		   short int balance = 4999;
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
				   flag =1;
			   }
		   }
		   else
		   flag =0;
		   while(1)
		   {
			   if (flag==1)
					{
						led_display_succ();
						led_display(balance);
						_delay_ms(3000);
						
					}
			   else
					{
						led_display_fail();
						_delay_ms(3000);
						led_display(balance);
						_delay_ms(3000);
						
					}
					
		   }
						
	return 0;
	
}

