struct AhoCorasick
{
	vector<map<char,int> > next; 
	// Trie, maps could be replaced with constant size arrays for small alphabets
	vector<int> back; // Longest suffix back-links, -1 if no backlink

	// Build Aho Corasick automaton
	AhoCorasick(const vector<string> &tab) : next(1,map<char,int>()), back(1,-1) {
		for(const string &s : tab) {
			int node = 0;
			for(const char &c : s) {
				if(!next[node].count(c)) {
					next[node][c] = next.size();
					back.push_back(-1);
					next.push_back(map<char,int>());
				}
				node = next[node][c];
			}
		}
		queue<int> q; q.push(0);
		while(!q.empty()) {
			int node = q.front();
			q.pop();
			for(const auto &x : next[node]) {
				int prec = back[node];
				while(prec != -1 && !next[prec].count(x.first))
					prec = back[prec];
				if(prec == -1)
					back[x.second] = 0;
				else
					back[x.second] = next[prec][x.first];
				q.push(x.second);
			}
		}
	}
};

