4 bitars räknare

typedef struct
{
	unsigned char ring : 4;	//D3-D0
	unsigned char john : 4;	//D7-D4
} ringJohn;

#define bDDR_RJ (*(volatile ringJohn*) &DDRB)
#define bPORT_RJ (*(volatile ringJohn*) &PORTB)

int ring4()
{
	static unsigned char r = 0b00000001;
	
	r = r << 1;
	
	if(r == 16)
	{
		r = 1;
	}
	
	return r;
}

int john4()
{
	static unsigned char j = 0;
		.
		.
		.
	return j;
}

int main()
{	
	DDRB = 0xFF;
	
	while(1)
	{
		bPORT_RJ.ring = ring4();
		bPORT_RJ.john = john4();
		_delay_ms(300);
	}
}