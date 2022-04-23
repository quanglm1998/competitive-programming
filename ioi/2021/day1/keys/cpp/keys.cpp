#include <bits/stdc++.h>

using namespace std;

vector<int> SolveSmall(int n, int m, const vector<int> &r, const vector<vector<pair<int, int>>> &adj) {
	vector<int> num(n, 0);

	auto Solve = [&](int s) {
		vector<int> used(n, false);
		vector<int> enable(n, false);
		vector<vector<int>> edge_list(n, vector<int>());
		queue<int> q;

		used[s] = true;
		q.push(s);

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			enable[r[u]] = true;

			for (auto [v, w] : adj[u]) {
				if (used[v]) continue;
				if (enable[w]) {
					used[v] = 1;
					q.push(v);
				} else {
					edge_list[w].push_back(v);
				}
			}

			for (auto v : edge_list[r[u]]) {
				if (used[v]) continue;
				used[v] = 1;
				q.push(v);
			}

			edge_list[r[u]].clear();
		}

		int res = 0;
		for (int i = 0; i < n; i++) {
			res += used[i];
		}
		return res;
	};

	for (int i = 0; i < n; i++) {
		num[i] = Solve(i);
	}
	int min_val = *min_element(num.begin(), num.end());
	vector<int> res(n, 0);
	for (int i = 0; i < n; i++) {
		res[i] = num[i] == min_val;
	}
	return res;
}

std::vector<int> find_reachable(std::vector<int> r, std::vector<int> u, std::vector<int> v, std::vector<int> c) {
	int n = r.size();
	int m = u.size();
	vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
	for (int i = 0; i < m; i++) {
		adj[u[i]].push_back({v[i], c[i]});
		adj[v[i]].push_back({u[i], c[i]});
	}
	
	vector<int> res(n, 0);
	bool f = 0;
	for (int i = 0; i < n; i++) {
		bool found = 0;
		for (auto [v, w] : adj[i]) {
			if (w == r[i]) {
				found = 1;
				break;
			}
		}
		if (!found) {
			res[i] = 1;
			f = 1;
		}
	}
	if (f) {
		return res;
	}

	
}
