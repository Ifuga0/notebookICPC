
const int NMAX=1e6+1;
const int RMAX=1e3;

bool notPrime[NMAX];

inline void sieve()
{
	for(int i=2;i<=RMAX;i++)
		if(!notPrime[i])
			for(int j=i*i;j<NMAX;j+=i)
				notPrime[j]=true;
}