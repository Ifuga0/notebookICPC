// Find all sub-palindromes in O(N)
struct Manacher{
// Array d[i] contains the radius of palindrome centered in i
vector<int> d1,d2;// d1,d2 for odd,even palindromes
int n;
// for even palindromes the center is on the right
Manacher(string &s) {
	n=s.size();
	d1.resize(n),d2.resize(n);
	// Odd palindromes :
	for(int i=0,l=0,r=-1;i<n;++i) {
		int k = (i>r) ? 1 : min(d1[l+r-i],r-i+1);
		while(0<=i-k&&i+k<n && s[i-k] == s[i+k]) {
			k++;
		}
		d1[i]=k--;
		if(i+k>r) {
			l=i-k;
			r=i+k;
		}
	}
	// Even palindromes :
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
			k++;
		}
		d2[i] = k--;
		if (i + k > r) {
			l = i - k - 1;
			r = i + k ;
		}
	}
}
pair<int,int> longestPalindrome() { // [a,b] format
	int len=0; pair<int,int> pal;
	for(int i=0;i<n;i++)
	{
		if(len<d1[i]*2-1) {
			len=d1[i]*2-1; pal={i-d1[i]+1,i+d1[i]-1};
		}
		if(len<d2[i]*2) {
			len=d2[i]*2; pal={i-d2[i],i+d2[i]-1};
		}
	}
	return pal;
}
};
