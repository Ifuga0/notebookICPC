// |S|log|S| time build
// LongestCommonPrefix is logarithmic
struct SuffixArray {
	const int L;
	const int inf=1e9;
	vector<pair<int,int> > M;
	vector<vector<int>> P;

	// Suffix array construction : ranks of suffixes in lexicographical order
	SuffixArray(const string& S) : L(S.size()), P(1,vector<int>(L,0)), M(L) {
		for(int i=0;i<L;++i) P[0][i] = int(S[i]);
		for(int skip=1, level=1; skip < L; skip*=2,++level) {
			P.push_back(vector<int>(L,0));
			for(itn i=0;i<L;++i)
				M[i]={{P[level-1][i],i+skip<L ? P[level-1][i+skip] : -inf},i};
			sort(M.begin(),M.end());
			for(int i=0;i<L;i++)
				P[level][M[i].second] = (i>0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
		}
	}

	// The suffix array is the inverse permutation of the result
	vector<int> GetSuffixArray() { return P.back(); }

	// Returns the size of the longest common prefix of s[i...L-1] and s[j...L-1]
	int LongestCommonPrefix(int i,int j) {
		int len=0;
		if(i==j) return L-i;
		for(int k=P.size()-1;k>=0 && i<L && j<L;--k) {
			if(P[k][i] == P[k][j]) {
				i+=1<<k;
				j+=1<<k;
				len+=1<<k;
			}
		}
		return len;
	}
};
