
const long long MOD=1e9+7;

long long exp(long long a,long long n)
{
	long long res=1;
	while(n)
	{
		if(n&1)
			res=(res*a)%MOD;
		a=(a*a)%MOD;
		n>>=1;
	}
	return res;
}