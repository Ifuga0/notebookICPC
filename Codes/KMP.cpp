
/// Preprocessing

int prefix[MMAX];

int i=1, j=0;
prefix[0]=0;
while(t[i]!='\0') {
	if(t[i]==t[j])
		prefix[i++]=++j;
	else if(j>0)
		j=prefix[j-1];
	else
		prefix[i++]=0;
}

/// Parsing

j=0;
vector<int> ind;
while(i<n) {
	if(s[i]==t[j]) {
		i++; j++;
		if(j==k)
		{
			ind.push_back(i-k);
			j=prefix[j-1];
		}
	}
	else if(j>0)
		j=prefix[j-1];
	else
		i++;
}

