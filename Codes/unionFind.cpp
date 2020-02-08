
int representant[NMAX];

void init(int n)
{
	for(int i=0;i<n;i++)
		representant[i]=-1;
}

int find(int u)
{
	if(representant[u]<0)
		return u;
	return representant[u]=find(representant[u]);
}

void union(int u,int v)
{
	int u=find(u);
	int v=find(v);
	if(u==v)
		return;
	if(representant[u]>representant[v])
		swap(u,v);
	representant[u]+=representant[v];
	representant[v]=u;
}