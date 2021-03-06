struct UnionFind {
	vector<int> rep;
	int nbComponents;
	UnionFind(int n) : rep(n,-1), nbComponents(n) {}
	int find(int u) {return rep[u]<0?u:rep[u]=find(rep[u]);}
	int size(int u) {return -rep[find(u)];}
	bool merge(int u,int v)
	{
		u=find(u),v=find(v);
		if(u==v) return false;
		nbComponents--;
		if(rep[u]>rep[v])
			swap(u,v);
		rep[u]+=rep[v];
		rep[v]=u;
		return true;
	}
};
