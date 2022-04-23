#include "dna.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

struct Data {
	int a[3][3];
	int* operator[](int u) {
		return a[u];
	}

	Data operator-(const Data &o) const {
		Data res;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				res[i][j] = a[i][j] - o.a[i][j];
			}
		}
		return res;
	}
};

Data sum[N];

void init(std::string a, std::string b) {
	map<char, int> m;
	m['A'] = 0;
	m['T'] = 1;
	m['C'] = 2;
	for (int i = 0; i < (int)a.size(); i++) {
		if (a[i] != b[i]) {
			sum[i][m[a[i]]][m[b[i]]]++;
		}
		if (i > 0) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					sum[i][j][k] += sum[i - 1][j][k];
				}
			}
		}
	}
}

Data GetRange(int x, int y) {
	if (x > 0) return sum[y] - sum[x - 1];
	return sum[y];
}

int get_distance(int x, int y) {
	Data now = GetRange(x, y);
	int res = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 3; j++) {
			int min_val = min(now[i][j], now[j][i]);
			res += min_val;
			now[i][j] -= min_val;
			now[j][i] -= min_val;
		}
	}

	bool all_zero = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			all_zero &= (now[i][j] == 0);
		}
	}

	if (all_zero) return res;

	if (now[0][1] != 0 && now[0][1] == now[1][2] && now[1][2] == now[2][0]) {
		res += now[0][1] * 2;
		return res;
	}
	if (now[0][2] != 0 && now[0][2] == now[2][1] && now[2][1] == now[1][0]) {
		res += now[0][2] * 2;
		return res;
	}
	return -1;
}
