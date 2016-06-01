int maxInt(int a, int b)
{
	if ( a > b )
		return a;
	else
		return b;
}


void minInt(int a, int b, int *min )
{
	if ( a > b )
		*min = b;
	else
		*min = a;
}


