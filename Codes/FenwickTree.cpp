// Compact and fast range sum query
#define lso(n) (n)&(-(n))
// /!\ all queries are 1-indexed
struct Fenwick{
	vector<int> tree; // 1-indexed
	Fenwick(int n) : tree(n+1,0) {}
	void add(int p,int v) { // add v to position p
		for(;p<tree.size();p+=lso(p)) tree[p]+=v; }
	int query(int p){ // query [1,p]
		int tot=0;
		for(;p>0;p-=lso(p)) tot+=tree[p];
		return tot;
	}
	int query(int a,int b){ return query(b)-query(a-1);} // query [a,b]
	void set(int p,int v){ add(p,v-query(p,p)); } // set position p to v
};
