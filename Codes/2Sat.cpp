// f = formula to satisfy, n=number of variables
struct clause{
	int x,y;
	bool a,b;
	clause(int x,bool a,int y,bool b) : x(x),a(a),y(y),b(b) {}
	bool is_sat(const vector<bool>& assign) const {
		return a==assign[x]||b==assign[y];
	}
};
using formule = vector<clause>;
bool is_sat(const formule& f, const vector<bool>& assign) {
	// auxilliary function
	for(int i=0;i<(int)f.size();i++) 
		if(!f[i].is_sat(assign)) return false;
	return true;
}

bool sat(const formule& f, int n, vector<bool> assign) {
	Tarjan tj(2*n); assign.assign(n,false);
	for(const auto& c:f) {
		tj.adj[2*c.x+ (!c.a)].push_back(2*c.y+c.b);
		tj.adj[2*c.y+ (!c.b)].push_back(2*c.x+c.a);
	}
	tj.compute();
	vector<vector<pair<int,bool> > > cc(tj.ncomp);
	for(int i=0;i<n;i++) {
		if(tj.comp[2*i]==tj.comp[2*i+1]) return false;
		cc[tj.comp[2*i]].push_back({i,false});
		cc[tj.comp[2*i+1]].push_back({i,true});
	}
	vector<bool> done(tj.ncomp,false);
	for(int i=0;i<tj.ncomp) if(!done[i]) {
		done[i]=true;
		for(auto& p : cc[i]) {
			assign[p.first] = p.second;
			done[tj.comp[2*p.first + !p.second]] = true;
		}
	}
}
