// You MUST input a vector of power of 2 size
// or it will be truncated

// To multiply two polynomials of degree < N
// compute their fft in >=2*N arrays
// then multiply point by point and apply fft_rev

const double PI=2*asin(1);

using vcd = vector<complex<double>>;

vcd fft(const vcd &as) {
	int n = as.size();
	int k = 0;
	while ((1 << k) < n) k++;
	n = 1 << k;
	vector<int> rev(n);
	rev[0] = 0;
	int high1 = -1;
	for (int i = 1; i < n; i++) {
		if ((i & (i - 1)) == 0) high1++;
		rev[i] = rev[i ^ (1 << high1)];
		rev[i] |= (1 << (k - high1 - 1));
	}

	vcd roots(n,1.);
	for (int i = 1; i < n/2; i++) {
		double alpha = 2 * PI * i / n;
		double ca=cos(alpha),sa=sin(alpha);
		roots[i] = complex<double>(ca, sa);
		roots[n-i] = complex<double>(ca, -sa);
	}

	vcd rows[2] = {vcd(n), vcd(n)};
	for (int i = 0; i < n; i++) rows[0][i] = as[rev[i]];

	int id = 0, nid = 1;
	for (int len = 1; len < n; len <<= 1, id ^= 1, nid ^= 1) {
		size_t rstep = roots.size() / (len * 2);
		for (int pdest = 0; pdest < n;) {
			int p1 = pdest;
			for (int i = 0; i < len; i++) {
				complex<double> val =
				    roots[i * rstep] * rows[id][p1 + len];
				rows[nid][pdest] = rows[id][p1] + val;
				rows[nid][pdest + len] = rows[id][p1] - val;
				pdest++, p1++;
			}
			pdest += len;
		}
	}
	return rows[id];
}

vcd fft_rev(const vcd &as) {
	vcd res = fft(as);
	for (auto &r : res) {
		r /= as.size();
	}
	reverse(res.begin() + 1, res.end());
	return res;
}
