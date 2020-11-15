
struct Arete
{
	int dest,len;
};

vector<Arete> adj[NMAX];
const int inf=1<<30;

// Complexité pire cas O(|V|.|E|), forêt de plus court chemins dans un graphe quelconque

void bellmanFord(vector<int> departs,int n)
{
	vector<int> dist(n,inf);
	vector<int> pred(n,-1);
	for(int d:departs)
	{
		dist[d]=0;
	}
	bool modif;
	for(int i=0;i<n;i++)
	{
		modif=false;
		for(int u=0;u<n;u++)
			for(Arete ar:adj[u])
				if(dist[ar.dest]<dist[u]+ar.len)
				{
					dist[ar.dest]=dist[u]+ar.len;
					pred[ar.dest]=u;
					modif=true;
				}
		if(!modif)
			break;
	}
	if(modif)
	{
		// Il y a un cycle négatif
	}
	
}