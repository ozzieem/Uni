/* Laboration 3-7 Strukturen på maskinnivå */
/* Projekt och assembly kod finns i kompendie Datorteknik */


typedef struct
{
	long long x,y,z,u,v; //Hur många bytes?
} data;

volatile data sData ={0x1011121314151617, 0x2021222324252627, ... };

__attribute__((noinline))
data dataF3( volatile data d)
{
	d.x=0;
	return d;
}

int main()
{
	
	// data d  - lokal variabel 40 bytes. I registret i stacken.
	volatile data d = dataF3(sData); // sData - global variabel 40 bytes
	
	
	
}




