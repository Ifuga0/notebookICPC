
struct Arete
{
	int dest,len;
};

vector<Arete> adj[NMAX];

// Pour les graphes creux, complexite O(|E|log|E|)
// Construit une forêt des plus courts chemins dans un graphe à pondération positive.

struct AreteDijkstra
{
	int dist,next,prev;
	bool operator<(const AreteDijkstra& other)	const
	{
		return dist>other.dist;
	}
};

void Dijkstra(vector<int> departs,int n) // ensemble des noeuds de départ et nombre de noeuds
{
	vector<int> dist(n,-1);
	vector<int> pred(n,-1);
	vector<bool> vu(n,false);
	priority_queue<AreteDijkstra> file;
	for(int d:departs)// Pour Prim on se contente d'un noeud quelconque
	{
		dist[d]=0;
		file.push({0,d,-1});
	}
	while(true)
	{
		while(!file.empty() && vu[file.top().next])
			file.pop();
		if(file.empty())
			break;
		int cur=file.top().next;
		dist[cur]=file.top().dist;
		pred[cur]=file.top().prev;
		vu[cur]=true;
		file.pop();
		for(Arete ar:adj[cur])
			if(!vu[ar.dest])
			{
				file.push({dist[cur]+ar.len,ar.dest,cur}); //retirer "dist[cur]+" pour Prim
			}
	}
}