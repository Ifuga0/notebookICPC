
long long pgcd(long long a,long long b)
{
	while(b)
	{
		a%=b;
		swap(a,b);
	}
	return a;
}