// Tarjan's algorithm to find strongly connected components in directed graph
// add arcs to adj and then call compute
struct Tarjan {
	int n;
	vector<vector<int>> adj;
	vector<int> comp,index,lowlink;
	stack<int> accu;
	int counter, nbComp;
	Tarjan(int n) : n(n), adj(n), comp(n,-1), index(n,-1), 
		lowlink(n,-1), counter(0), nbComp(0) {}
	void dfs(int u) {
		index[u] = lowlink[u] = counter++;
		accu.push(u);
		for(int v:adj[u]) {
			if(index[v]==-1) dfs(v);
			if(comp[v]==-1)
				lowlink[u]=min(lowlink[u],lowlink[v]);
		}
		if(lowlink[u]==index[u]) {
			int v; do {
				v=accu.top(); accu.pop();
				comp[v]=ncomp;
			} while(u!=v);
			++ncomp;
		}
	}
	void compute(){
		for(int i=0;i<n;i++)
			if(index[i]==-1) dfs(i);
	}
};
