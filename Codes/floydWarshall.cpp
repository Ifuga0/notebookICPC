
for(int piv=0;piv<n;piv++)
	for(int deb=0;deb<n;deb++)
		for(int fin=0;fin<n;fin++)
		{
			int ndist=dist[deb][piv]+dist[piv][fin];
			if(dist[deb][fin] > ndist)
			{
				dist[deb][fin] = ndist;
				pred[deb][fin] = pred[piv][fin];
			}
		}