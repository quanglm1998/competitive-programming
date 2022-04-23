#include <bits/stdc++.h>

using namespace std;

const int N = 510;
const long long MAX = 1000000000000ll;

int n, m, s, r;
vector<int> adj[N];
long long dp[N][N];
pair<vector<int>, int> a[N];
vector<int> lsRecipes[N];

void solve(int test) {
    cout << "Case #" << test << ": ";

    cin >> n >> m >> s >> r;
    //init
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        for (int j = 1; j <= s; j++) {
            dp[i][j] = -1;
        }
    }
    for (int i = 1; i <= r; i++) {
        a[i].first.clear();
    }
    for (int i = 1; i <= s; i++) {
        lsRecipes[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    set<pair<long long, pair<int, int>>> ss;

    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        for (int j = 1; j <= c; j++) {
            int u;
            cin >> u;
            dp[i][u] = 0;
            ss.insert({0, {i, u}});
        }
    }

    for (int i = 1; i <= r; i++) {
        int k;
        cin >> k;
        a[i].first.assign(k, 0);
        for (int &u : a[i].first) {
            cin >> u;
            lsRecipes[u].push_back(i);
        }
        cin >> a[i].second;
    }

    for (int i = 1; i <= s; i++) {
        sort(lsRecipes[i].begin(), lsRecipes[i].end());
        lsRecipes[i].resize(unique(lsRecipes[i].begin(), lsRecipes[i].end()) - lsRecipes[i].begin());
    }

    while (!ss.empty()) {
        long long dist = ss.begin()->first;
        pair<int, int> u = ss.begin()->second;
        ss.erase(ss.begin());

        // go through edges
        for (int v : adj[u.first]) {
            if (dp[v][u.second] == -1 || dp[v][u.second] > min(MAX, dist + 1)) {
                ss.erase({dp[v][u.second], {v, u.second}});
                dp[v][u.second] = min(MAX, dist + 1);
                ss.insert({dp[v][u.second], {v, u.second}});
            }
        }

        // go through recipes
        for (int id : lsRecipes[u.second]) {
            long long sum = 0;
            int f = 0;
            for (auto v : a[id].first) {
                if (dp[u.first][v] == -1) {
                    f = 1;
                    break;
                }
                sum += dp[u.first][v];
                sum = min(sum, MAX);
            }
            if (f) continue;
            if (dp[u.first][a[id].second] == -1 || dp[u.first][a[id].second] > sum) {
                ss.erase({dp[u.first][a[id].second], {u.first, a[id].second}});
                dp[u.first][a[id].second] = sum;
                ss.insert({dp[u.first][a[id].second], {u.first, a[id].second}});
            }
        }
    }

    long long res = MAX;
    for (int i = 1; i <= n; i++) {
        if (dp[i][1] != -1) res = min(res, dp[i][1]);
    }
    cout << (res >= MAX ? -1 : res) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}