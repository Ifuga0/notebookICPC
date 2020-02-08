
const long long MOD=1e9+7;
const long long MATSIZE=2;


struct Matrix
{
	long long v[MATSIZE][MATSIZE];
	Matrix operator *(const Matrix& other) 
	{
		Matrix res;
		for(int i=0;i<MATSIZE;i++)
			for(int j=0;j<MATSIZE;j++)
			{
				res.v[i][j]=0;
				for(int k=0;k<MATSIZE;k++)
				{
					res.v[i][j]+=(v[i][k]*other.v[k][j])%MOD;
				}
				res.v[i][j]%=MOD;
			}
		return res;
	}
}

Matrix identity()
{
	Matrix m;
	for(int i=0;i<MATSIZE;i++)
		for(int j=0;j<MATSIZE;j++)
			m.v[i][j]=(i==j);
	return m;
}

long long expMat(Matrix a,long long n)
{
	Matrix res=identity();
	while(n)
	{
		if(n&1)
			res=res*a;
		a=a*a;
		n>>=1;
	}
	return res;
}