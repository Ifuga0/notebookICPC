// maximum matching (graph not necessarily bipartite)
// N^4 running time

struct EdmondsBlossom{
	int N;
	vector<int> match,vis;
	EdmondsBlossom(int N): N(N){}
	void couple (int, int m) { match[n]=m; match[m]=n; }

	//returns true if something interesting has been found,
	// thus an augmenting path or a blossom
	bool dfs(int n, vector<vector<bool>> &conn, vector<int>& blossom) {
		vis[n]=0;
		for(int i=0;i<N;i++) if(conn[n][i]) {
			if(vis[i]==-1) {
				vis[i]=1;
				if(match[i]==-1 || dfs(match[i], conn, blossom)) {
					couple(n,i); return true; }
			}
			if(vis[i]==0 || blossom.size()) { // found flower
				blossom.push_back(i); blossom.push_back(n);
				if(n==blossom[0]) {match[n]=-1; return true; }
				return false;
			}
		}
		return false;
	}

	// search for an augmenting path
	bool augment(vector<vector<bool>> &conn) {
		for(int m=0;m<N;m++) if(match[m]==-1) {
			vector<int> blossom;
			vis=vector<int>(N,-1);
			if(!dfs(m,conn,blossom)) continue;
			if(blossom.size()==0) return true; // augmenting path found

			// blossom is found so build shrunken graph
			int base=blossom[0], S=blossom.size();
			vector<vector<int> newconn=conn;
			for(int i=1;i<S-1;i++)
				for(int j=0;j<N;j++)
					newconn[base][j]=newconn[j][base]|=conn[blossom[i]][j];
			for(int i=1;i<S-1;i++)
				for(int j=0;j<N;j++)
					newconn[blossom[i]][j]=newconn[j][blossom[i]]=0;
			newconn[base][base]=0; // is now the new graph
			if(!augment(newconn)) return false;
			int n=match[base];

			// if n!=-1 the augmenting path ended on this blossom
			if(n!=-1) for(int i=0;i<S;i++) if(conn[blossom[i]][n]) {
				couple(blossom[i],n);
				if(i&1) for(int j=i+1; j<S; j+=2) couple(blossom[j],blossom[j+1]);
				else for(int j=0;j<i;j+=2) couple(blossom[j],blossom[j+1]);
				break;
			}
			return true;
		}
		return false;
	}
	
	// conn is a NxN adjacency matrix
	// returns size of max matching
	// matching can be found in match vector
	int compute(vector<vector<int>> &conn) {
		int res=0;
		match=vector<int>(N,-1);
		while(augment(conn)) res++;
		return res;
	}
}
