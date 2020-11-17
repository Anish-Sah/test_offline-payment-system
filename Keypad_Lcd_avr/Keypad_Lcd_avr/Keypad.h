#ifndef F_CPU

# define F_CPU 16000000UL // clock speed is 16MHz

#endif

void Init()
{
	KeypadDirectionRegister = 0x0F;
	KeypadPortControl = 0xF0;
}

char GetKey()
{
	//Is Keypad pressed
	if(KeypadPortValue == 0xF0) 	return '!' ;
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
	
	unsigned char DisplayValue =0;

	if(keyPressCode==0xEB)		DisplayValue='1';
	if(keyPressCode==0xDB)		DisplayValue='2';
	if(keyPressCode==0xBB)		DisplayValue='3';
	if(keyPressCode==0xED)		DisplayValue='4';
	if(keyPressCode==0xDD)		DisplayValue='5';
	if(keyPressCode==0xBD)		DisplayValue='6';
	if(keyPressCode==0xEE)		DisplayValue='7';
	if(keyPressCode==0xDE)		DisplayValue='8';
	if(keyPressCode==0xBE)		DisplayValue='9';
	if(keyPressCode==0xD7)		DisplayValue='0';
	if(keyPressCode==0xE7)		DisplayValue='N';
	if(keyPressCode==0xB7)		DisplayValue='=';
	if(keyPressCode==0x77)		DisplayValue='+';
	if(keyPressCode==0x7B)		DisplayValue='-';
	if(keyPressCode==0x7D)		DisplayValue='x';
	if(keyPressCode==0x7E)		DisplayValue='/';
	return DisplayValue;
	Init();										//Resetting all the led and keypad
	
}