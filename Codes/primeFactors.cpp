
const int NMAX=1e6+1;
int leastPrimeFactor[NMAX];
int primes[NMAX]; int nbPrimes=0;

void sieve()
{
	for(int i=2;i<NMAX;i++)
	{
		if(!leastPrimeFactor[i])
		{
			leastPrimeFactor[i]=i;
			primes[nbPrimes++]=i;
		}
		for(int j=0;j<nbPrimes && primes[j] <= leastPrimeFactor[i] && i*primes[j] < NMAX;j++)
			leastPrimeFactor[i*primes[j]]=primes[j];
	}
}