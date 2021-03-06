struct Ukkonen {
	const int inf = 1e9;
	vector<char> s;
	vector<int> len,fpos,link; 
	// fpos[i] is the first char in s for node i
	// len[i] is the length of the substring for node i
	vector<map<char,int>> to; // adjacency in the tree (give first char)
	int sz, n, node, pos;

	Ukkonen() : len(1,inf), fpos(1), link(1), to(1), sz(1), n(0), node(0), pos(0) {}
	int make_node(int _pos, int_len) {
		fpos.push_back(_pos);
		len.push_back(_len);
		to.push_back(map<T,int>());
		link.push_back(0);
		return sz++;
	}

	void go_edge() {
		while(pos > len[to[node][s[n-pos]]]) {
			node = to[node][s[n-pos]];
			pos -= len[node];
		}
	}

	void add_letter(char c) {
		s.push_back(c);
		pos++;
		n++;
		int last=0;
		while(pos > 0) {
			go_edge();
			char edge = s[n-pos];
			int &v = to[node][edge];
			char t = s[fpos[v]+pos-1];
			if(v==0) {
				v = make_node(n-pos, inf);
				link[last] = node;
				last = 0;
			} else if(t == c) {
				link[last]=node;
				return;
			} else {
				int u = make_node(fpos[v], pos-1);
				to[u][c] = make_node(n-1, inf);
				to[u][t] = v;
				fpos[v] += pos-1;
				len[v] -= pos-1;
				v = u;
				link[last] = u;
				last = u;
			}
			if(node==0)
				pos--;
			else
				node=link[node];
		}
	}
};
