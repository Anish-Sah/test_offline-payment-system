//To use as a sender msg[8] should be 0 and to use as a receiver msg[8] should be 1
//msg should be of 9 bit only
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define FOSC 1000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1        

void USART_Init(unsigned int ubrr)
{
	UBRRH =(unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB= (1<<RXEN)|(1<<TXEN);              //Enabling receiver and transmitter
	UCSRC = (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);   //making 2 stop bit and sending 8 bit
}
unsigned char USART_Receive(void)
{
	while(!( UCSRA &(1<<RXC)));           //checking if the receiver is empty
	_delay_ms(200);
	return UDR;
	
}
//this function receive long string chars
//make sure buffer size is enough
//firstly read from usart the data and write to string array
//after compare last data with '\0' if it is null terminate the reading
void UART_ReadStringData(char *str){
	
	char c; int count=0;
	unsigned char comp[10];
	
	while(count<10)
	{
		count++;
		
		c=USART_Receive();
		*str=c;
		str++;
		comp[count]=c;
		if(count==9)
		break;
		
		
	}
  
	if(comp[1]=='7' && comp[2]=='2' && comp[3]=='3' && comp[4]=='0' && comp[5]=='1' && comp[6]=='1' && comp[7]=='2' && comp[8]=='3' && comp[9]=='1')
	{
		PORTC=(1<<PORTC0);
		_delay_ms(500);
		PORTC=(0<<PORTC0);
	}
	return;
}
//function to send char/data
void USART_Transmit(unsigned char data, int x)
{
	
	while(!( UCSRA &(1<<UDRE)));   //UDRE to check is transmitter is ready
	_delay_ms(200);
	UDR= data;
}
//function to send string
void USART_WriteStringdata(char* StringPtr){
	int count=0;
	while(*StringPtr !='\0'){
		count++;
		USART_Transmit(*StringPtr, count);
		
	StringPtr++;
	}	
}
int main(void)

{
	DDRA&=(~(1<<PA0));           //pin0 of portA as INPUT
	PORTA|=(1<<PA0);
	USART_Init(MYUBRR);
	DDRC|=(1<<PC0);              //Port C as output
	char msg[9]="723011231"; 
	char str1[20];             
	while(1)
	{
		
		if (msg[8]=='0')     //0 for receive
		{
			UART_ReadStringData(str1);		
		}
		if (msg[8]=='1')     //1 for transmit
		{
			if(!(PINA&(1<<PA0))){
				USART_WriteStringdata(msg); // Pass the string to the USART_putstring function and sends it over the serial
				_delay_ms(1000);         // Delay for 5 seconds so it will re-send the string every 5 seconds
			}
			
		}
		
	}
	return 0;
}









