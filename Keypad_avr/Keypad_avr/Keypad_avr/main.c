#define  F_CPU 16000000UL

#define KeypadDirectionRegister		DDRB
#define KeypadPortControl			PORTB
#define KeypadPortValue				PINB

#include <avr/io.h>
#include <util/delay.h>

void Init()
{
	DDRC = 0xFF;		//8-bit LED for key output
	PORTC=0x00;			//Initial leds are off
	KeypadDirectionRegister = 0x0F;
	KeypadPortControl = 0xF0;
}

void GetKey()
{
	//Is Keypad pressed
	if(KeypadPortValue == 0xF0) return;
	_delay_ms(50);
	
	//Scan the Keypad
	uint8_t keyPressCode;
	uint8_t keyUpperNib = KeypadPortValue;			//Storing the initial upper nibble of the key pressed
	KeypadPortControl ^= 0xFF;						//Reversing the Port control
	KeypadDirectionRegister ^= 0xFF;				//Reversing the data direction
	asm volatile ("nop");							//No operation instruction (time for reversing data direction)
	asm volatile ("nop");							
	uint8_t keyLowerNib = KeypadPortValue;			//Storing the Lower Nibble of key pressed
	keyLowerNib &= 0x0F;							//Resetting Upper Nibble changes of Port Value
	keyPressCode = keyUpperNib + keyLowerNib;		//Combining the Upper and Lower Nibbles
	PORTC = keyPressCode;							//Displaying the Key Pressed in the 8-bit led
	_delay_ms(2000);
	Init();										//Resetting all the led and keypad

}



int main(void)

{
	Init();
	while(1)
	{
			GetKey();				//Getting key by polling method
	}
	
	return 0;
}


