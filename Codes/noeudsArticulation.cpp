
vector<int> adj[NMAX];
char vu[NMAX];
int prof[NMAX];
int pere[NMAX];
int remontee[NMAX];
int taille[NMAX];
int nbFils[NMAX];
int n,m;
vector<int> articulations;

void dfs(int u,int p)
{
	pere[u]=p;
	prof[u]=prof[p]+1;
	remontee[u]=prof[u];
	taille[u]=1;
	vu[u]=1;
	for(int v:adj[u])
	{
		if(!vu[v])
		{
			dfs(v,u);
			nbFils[u]++;
			taille[u]+=taille[v];
		}
		if(v!=p)
			remontee[u]=min(remontee[u],remontee[v]);
	}
	if(remontee[u]==prof[u] && p && taille[u]>1 && !(vu[u]&2))
	{
		articulations.push_back(u);
		vu[u]|=2; //marquer u comme noeud d'articulation
	}
	if(!p && nbFils[u]>1 && !(vu[u]&2))
	{
		articulations.push_back(u);
		vu[u]|=2; //marquer u comme noeud d'articulation
	}
	if(remontee[u]==prof[u] && p && pere[p] && !(vu[p]&2))
	{
		articulations.push_back(p);
		vu[p]|=2; //marquer u comme noeud d'articulation
	}
}


