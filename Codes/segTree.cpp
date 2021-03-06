const int HAUTEUR=10;
const int TREE_SIZE=(1<<(HAUTEUR+1));
const int FEUILLES=(1<<HAUTEUR);
int segTree[TREE_SIZE];

inline int operation(int a,int b) {
	return a+b;
}

inline int neutre() {
	return 0;
}
// Remplir à partir de FEUILLES avant l'appel
// Attention à remplir le trou après avec le neutre si != 0
void init() {
	for(int i=FEUILLES-1;i>0;i--)
	{
		segTree[i]=operation(segTree[2*i],segTree[2*i+1]);		
	}
}

void update(int i,int v) {
	segTree[i]=v;
	i>>=1;
	while(i)
	{
		segTree[i]=operation(segTree[2*i],segTree[2*i+1]);
		i>>=1;
	}
}

int evalItv(int a,int b)	// [a,b] , bornes incluses
{
	a+=FEUILLES; b+=FEUILLES;
	int res=neutre();
	while(a<b)
	{
		if(a&1)
		{
			res=operation(res,segTree[a]);
			a++;
		}
		if(!(b&1))
		{
			res=operation(res,segTree[b]);
			b--;
		}
		a>>=1;
		b>>=1;
	}
	if(a==b)
	{
		res=operation(res,segTree[a]);
	}
	return res;
}

