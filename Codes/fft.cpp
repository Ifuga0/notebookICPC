#include "kernel/fft.h"

using vcd = std::vector<std::complex<double>>;

std::vector<std::complex<double>> fft(
    const std::vector<std::complex<double>> &as) {
	int n = as.size();
	int k = 0;
	while ((1 << k) < n) k++;
	n = 1 << k;
	std::vector<int> rev(n);
	rev[0] = 0;
	int high1 = -1;
	for (int i = 1; i < n; i++) {
		if ((i & (i - 1)) == 0) high1++;
		rev[i] = rev[i ^ (1 << high1)];
		rev[i] |= (1 << (k - high1 - 1));
	}

	std::vector<std::complex<double>> roots(n);
	for (int i = 0; i < n; i++) {
		double alpha = 2 * M_PI * i / n;
		roots[i] = std::complex<double>(cos(alpha), sin(alpha));
	}

	vcd rows[2] = {vcd(n), vcd(n)};
	for (int i = 0; i < n; i++) rows[0][i] = as[rev[i]];

	int id = 0, nid = 1;
	for (int len = 1; len < n; len <<= 1, id ^= 1, nid ^= 1) {
		std::size_t rstep = roots.size() / (len * 2);
		for (int pdest = 0; pdest < n;) {
			int p1 = pdest;
			for (int i = 0; i < len; i++) {
				std::complex<double> val =
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

std::vector<std::complex<double>> fft_rev(
    const std::vector<std::complex<double>> &as) {
	std::vector<std::complex<double>> res = fft(as);
	for (auto &r : res) {
		r /= as.size();
	}
	reverse(res.begin() + 1, res.end());
	return res;
}
