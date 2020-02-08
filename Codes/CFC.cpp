
const int NMAX=100001;
vector<int> adj[NMAX];
vector<int> adjInv[NMAX];
int ordreParcours[NMAX]; int idParcours=0;
char visite[NMAX]; int idVisite=1;
vector<int> cfc[NMAX]; int nbCFC=0;

void dfs1(int u)
{
	visite[u]=idVisite;
	for(int v:adj[u])
		if(visite[v]!=idVisite)
			dfs1(v);
	ordreParcours[idParcours++]=u;
}

void dfsCFC(int u)
{
	cfc[nbCFC].push_back(u);
	visite[u]=idVisite;
	for(int v:adjInv[u])
		if(visite[v]!=idVisite)
			dfsCFC(v);
}

void construitCFC(int n)
{
	for(int i=0;i<n;i++)
		if(visite[i]!=idVisite)
			dfs1(i);
	idVisite++;
	for(int i=n-1;i>=0;i--)
	{
		int u=ordreParcours[i];
		if(visite[u]!=idVisite)
		{
			dfsCFC(u);
			nbCFC++;
		}
	}
}