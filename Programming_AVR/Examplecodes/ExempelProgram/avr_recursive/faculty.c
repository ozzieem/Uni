char RFac(char n)
{
	if ( n == 0 )
	{
		return 1;
	}
	else
	{
		return n*RFac(n-1);
	}
}
