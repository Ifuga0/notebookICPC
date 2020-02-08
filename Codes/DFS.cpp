
vector<int> adj[NMAX];

char etat[NMAX];

const char EN_COURS=1;
const char VISITE=2;

void parcours(int u)
{
	etat[u]=EN_COURS;
	for(int v : adj[u])
		if(!etat[v])
			parcours(v);
		else if(etat[v]==EN_COURS)
		{
			// ARC RETOUR
		}
		else
		{
			// ARC TRANSVERSE OU ARC AVANT
		}
	etat[u]=VISITE;
}