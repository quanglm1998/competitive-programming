#include <bits/stdc++.h>

using namespace std;

const int N = 10000000;

class PrimeSubstrings {
    int p[N];
    int last[N];
    int p10[8] = {1,
                10, 
                100, 
                1000, 
                10000, 
                100000, 
                1000000, 
                10000000};
    set<int> s;
    int start = -1;

	public:

    void dfs(int u, int l) {
        s.insert(u);
        // cout << u << endl;
        for (int i = 1; i <= 9 && start == -1; i += 2) {
            int nxt = u * 10 - p[l] + i;
            if (p10[l - 1] > nxt || p10[l] <= nxt || nxt == u) continue;
            if (!p[nxt]) {
                if (last[nxt] == -1) {
                    last[nxt] = u;
                    dfs(nxt, l);
                } else {
                    if (s.find(nxt) != s.end()) {
                        last[nxt] = u;
                        start = u;
                        return;
                    } 
                }
            }
        }
    }

	string construct(int n, int l) {
        start = -1;
		if (l == 1) {
            string res = "";
            for (int i = 1; i <= n; i++) {
                res += '3';
            }
            return res;
        }
        memset(p, 0, sizeof p);
        
        for (int i = 2; i < N; i++) {
            if (!p[i]) {
                for (int j = i + i; j < N; j += i) {
                    p[j] = 1;
                }
            }
        }

        memset(last, -1, sizeof last);

        for (int i = p10[l - 1]; i < p10[l] && start == -1; i++) {
            if (p[i]) continue;
            last[i] = 0;
            s.clear();
            dfs(i, l);
        }

        vector<int> ls;
        cout << start << endl;
        // ls.push_back(start);
        // while (1) {

        // }
        return "";
	}
};
