// Min Cost Bipartite matching
struct Hungarian {
	vector<vector<int>> cost,match;
	Hungarian(int n): cost(n,vector<int>(n,0));

	vector<vector<int>> label;
	vector<int> slack, slackx, parent;
	vector<bool> S,T;
	queue<int> file;
	int n,matchingSize;
	void augmentPath(int j) {
		//Invert edges on the path
		while(j>=0) {
			int tmp = match[0][parent[j]];
			match[0][parent[j]] = j;
			match[1][j] = parent[j];
			j=tmp;
		}
		++matchingSize;
	}
	bool addEdge(int i,int j) {
		int k=match[1][j];
		parent[j]=i;
		if(k<0) { augmentPath(j); return true; }
		S[k] = T[j] = true;
		file.push(k);
		for(int y=0;y<n;y++) {
			if(cost[k][y] - label[0][k] - label[1][y] < slack[y]) {
				slack[y] = cost[k][y] - label[0][k] - label[1][y];
				slackx[y] = k;
			}
		}
		return false;
	}
	void findAugmentingPath() {
		int root = -1;
		S.assign(n,false);
		T.assign(n,false);
		parent.assign(n,-1);
		file = queue<int>();
		// Initial queue, start from uncovered vertices
		for(int i=0;i<n;i++) 
			if(match[0][i]<0) { file.push(root=i); S[i]=true; break;}
		for(int j=0;j<n;j++) { // Initialize slack array
			slack[j] = cost[root][j] - label[0][root] - label[1][j];
			slackx[j] = root;
		}
		while(true) {
			// Breadth first search
			while(!file.empty()) {
				int i = file.front(); file.pop();
				for(int j=0;j<(int)cost.size();j++)
					if(!T[j] && label[0][i] + label[1][j] == cost[i][j] 
						&& addEdge(i,j)) return;
			}
			// No augmenting path found, update labels
			updateLabels();
			// try to add new edges to the augmenting tree
			file = queue<int>();
			for(int j=0;j<n;j++)
				if(!T[j] && slack[j]==0 && addEdge(slackx[j],j)) return;
		}
	}
	void updateLabels() {
		// Compute delta using slack array
		int delta = numer_limits<int>::max();
		for(int j=0;j<n;j++)
			if(!T[j]) delta = min(delta,slack[j]);
		// Update labels of vertices from S and T
		for(int i=0;i<n;i++) if(S[i]) label[0][i] += delta;
		for(int j=0;j<n;j++) if(T[j]) label[1][i] -= delta;
		// Update slack array
		for(int j=0;j<n;j++) if(!T[j]) slack[j] -= delta;
	}
	int minimize() {
		// Initialisation
		n = cost.size();
		slack.resize(n); slackx.resize(n);
		label.assign(2,vector<int>(n,0));
		match.assign(2,vector<int>(n,-1));
		// Main loop
		for(matchingSize = 0; matchingSize<n;)
			findAugmentingPath();
		// Return the resulting cost
		int sum = 0;
		for(int i=0;i<n;i++) sum+=cost[i][match[0][i]];
		return sum;
	}
};
