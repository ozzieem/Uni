int add2(int a, int b)
{
	return a+b;
}


long add4(long a, long b)
{
	return a+b;
}


unsigned char RFac(unsigned char n)
{
	if ( n == 0 )
		return 1;
	else
		return n*RFac(n-1);

}

unsigned char IFac(unsigned char n)
{
	unsigned char r=1;

	for ( ; n>0; n--)
		r=n*r;

	return r;

}


