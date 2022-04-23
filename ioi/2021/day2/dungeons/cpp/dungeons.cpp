#include "dungeons.h"
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<int> values;
bool all_equal = true;
int n;
vector<int> s, p, w, l;

void init(int N, std::vector<int> S, std::vector<int> P, std::vector<int> W, std::vector<int> L) {
	s = S;
	p = P;
	w = W;
	l = L;
	n = N;

	for (auto u : s) {
		values.push_back(u);
	}
	for (int i = 0; i < n; i++) {
		all_equal &= (s[i] == p[i]);
	}

	sort(values.begin(), values.end());
	values.resize(unique(values.begin(), values.end()) - values.begin());
	if (values.size() <= 5) {

	}
}

long long SolveNaive(int x, int z) {
	long long res = z;
	while (x != n) {
		if (res >= s[x]) {
			res += s[x];
			x = w[x];
		} else {
			res += p[x];
			x = l[x];
		}
	}
	return res;
}

long long SolveAllEqual(int x, int z) {

}

long long simulate(int x, int z) {
	if (all_equal) return SolveAllEqual(x, z);
	return SolveNaive();
}

