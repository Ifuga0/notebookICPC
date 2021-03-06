// Fonction indicatrice d'Euler
void eulerSieve(vector<int> &eulerPhi, unsigned long long limit) {
	for(int i=1;i<limit;i++)
		eulerPhi[i]=i;
	for(int i=2;i<limit;i++) {
		if(isPrime[i]) {
			for(int j=i;j<limit;j+=i)
				eulerPhi[j] -= eulerPhi[j]/i;
		}
	}
}
