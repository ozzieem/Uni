typedef struct
{
	unsigned char D0 : 1;
	unsigned char D1 : 1;
	unsigned char D2 : 1;
	unsigned char D3 : 1;
	unsigned char D4 : 1;
	unsigned char D5 : 1;
	unsigned char D6 : 1;
	unsigned char D7 : 1;
	
} byteRegister;

Se sidan 66 i kompendiet.

______________________________________________________________________

Ex1 Tända/släcka lysdiod med en monostabil tryckknapp
	(Behöver inte hålla en tryckknapp för att behålla intryckt värde)

	Lösning1

int main()
{
	bDDRB.D0 = 1;
	while(1)
	{
		bPORTB.D0 = bPINA.D6;
	}
}

	Lösning2 (Flankkänslig tryckknapp)
	
int SW6()
{
	static char toggle = 1;		//PB0-toggle
	static char old = 1;
	
	char new = bPINA.D6;
	
	if(old && !new)
	{
		toggle = !toggle;
		
	}
	old = new;
	
	return toggle;
	
}

int main()	//Lösning2 main
{
		bDDRB.D0 = 1;
	while(1)
	{
		bPORTB.D0 = SW6();
	}
	
}





