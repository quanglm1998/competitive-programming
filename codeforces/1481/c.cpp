#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        vector<int> b(n);
        vector<int> c(m);
        for (int &u : a) {
            cin >> u;
        }
        for (int &u : b) {
            cin >> u;
        }
        for (int &u : c) {
            cin >> u;
        }
        vector<bool> ok(n, 0);
        vector<int> res(m, 0);
        vector<deque<int>> q(n + 1);
        int firstUsed = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] == b[i]) {
                q[b[i]].push_back(i);
                ok[i] = 1;
            } else {
                q[b[i]].push_front(i);
            }
        }
        bool f = 0;
        for (int i = m - 1; i >= 0; i--) {
            if (q[c[i]].empty()) {
                if (firstUsed == -1) {
                    f = 1;
                    break;
                } else {
                    res[i] = firstUsed;
                }
            } else {
                int u = q[c[i]].front();
                q[c[i]].pop_front();
                q[c[i]].push_back(u);
                ok[u] = 1;
                res[i] = u;
                if (firstUsed == -1) firstUsed = u;
            }
        }
        for (int i = 0; i < n; i++) {
            if (!ok[i]) {
                f = 1;
                break;
            }
        }
        if (f) cout << "NO\n";
        else {
            cout << "YES\n";
            for (int u : res) cout << u + 1 << ' ';
                cout << '\n';
        }
    }
    return 0;
}