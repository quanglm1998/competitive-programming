#include <bits/stdc++.h>

using namespace std;
#define int long long

const int N = 1000010;

int n, m;
long long c[N];
vector<int> adj[N];
long long sum[N];
int last[N];

main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
        }
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            sum[i] = 0ll;
            last[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }
        long long res = 0;
        for (int i = 1; i <= n; i++) {
            set<int> changed;
            for (int u : adj[i]) {
                if (last[u]) {
                    changed.insert(last[u]);
                    sum[last[u]] -= c[u];
                }
                last[u] = i;
                sum[i] += c[u];
            }
            changed.insert(i);
            for (int u : changed) {
                res = __gcd(res, sum[u]);
            }
            cout << "# " << i << endl;
            for (int j = 1; j <= i; j++) cout << sum[j] << ' ';
                cout << endl;
        }
        cout << res << '\n';
    }       
    return 0;
}