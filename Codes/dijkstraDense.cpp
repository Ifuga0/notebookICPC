
struct Arete
{
	int dest,len;
};

vector<Arete> adj[NMAX];

// Pour les graphes denses , complexite O(|V|^2)
// Construit une forêt des plus courts chemins dans un graphe à pondération positive.


void Dijkstra(vector<int> departs,int n) // ensemble des noeuds de départ et nombre de noeuds
{
	vector<int> dist(n,-1);
	vector<int> pred(n,-1);
	vector<bool> vu(n,false);
	for(int d:departs) // Pour prim on se contente d'un noeud quelconque
		dist[d]=0;
	while(true)
	{
		int iMin=-1;
		for(int i=0;i<n;i++)
		{
			if(!vu[i] && (iMin==-1 || dist[i]<dist[iMin]))
			{
				iMin=i;
			} 
		}
		if(iMin==-1)
			break;
		vu[iMin]=true;
		for(Arete ar:adj[iMin])
			if(!vu[ar.dest])
			{
				int ndist=dist[iMin]+ar.len; // Pour prim retirer "dist[iMin]
				if(ndist<dist[ar.dest])
				{
					dist[ar.dest]=ndist;
					pred[ar.dest]=iMin;
				}
			}
	}
	
}