#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1000010;
const double INF = 1e18;
const int MOD = 1000000007;

int n, m, k;
int x[N], y[N], p[N], h[N], l[N];
vector<pair<int, int>> adj[N];
vector<int> events[N];
int lv[N];
int dp[N];
int res = 1;

struct Hull {
    set<pair<pair<int, int>, double>> s;

    Hull() {
        s.empty();
    }


    // x <= 0
    void add(int x, int y) {
        double cur = -INF;
        while (s.lower_bound({{x, y}, -INF}) != s.begin()) {
            auto it = s.lower_bound({{x, y}, -INF});
            it--;
            int xx = it->first->first;
            int yy = it->first->second;
            double curcur = it->second;

            if (xx == x) {
                if (yy <= y) {
                    return;
                }
                s.erase(it);
                continue;
            }

            cur = 1.0 * (y - yy) / (xx - x);
            if (cur <= curcur) {
                s.erase(it);
                continue;
            }
            break;
        }

        while (s.lower_bound({{x, y}, -INF}) != s.end()) {
            auto it = s.lower_bound({{x, y}, -INF});
            int xx = it->first->first;
            int yy = it->first->second;
            double curcur = it->second;

            if (xx == x) {
                if (yy <= y) return;
                s.erase(it);
                continue;
            }

            double now = 1.0 * (y - yy) / (xx - x);
            if (now <= cur) {
                return;
            }
            
        }
    }   
};

Hull *hull[N];

void dfs(int u) {
    hull[u] = new Hull();
    if (adj[u].empty()) {
        dp[u] = 0;
        
    } else {
        for (auto v : adj[u]) {
            lv[v.first] = lv[u] + v.second;
            dfs(v.first);
        }
    }
}

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n >> m >> k;

    int a, b, c, d;

    for (int i = 1; i <= k; i++) {
        cin >> p[i];
    }
    cin >> a >> b >> c;
    for (int i = k + 1; i <= n; i++) {
        p[i] = (a * p[i - 2] + b * p[i - 1] + c) % (i - 1) + 1;
    }

    for (int i = 1; i <= k; i++) {
        cin >> l[i];
    }
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; i++) {
        l[i] = (a * l[i - 2] + b * l[i - 1] + c) % d + 1;
    }

    for (int i = 1; i <= k; i++) {
        cin >> h[i];
    }
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; i++) {
        h[i] = (a * h[i - 2] + b * h[i - 1] + c) % d + 1;
    }

    for (int i = 1; i <= k; i++) {
        cin >> x[i];
    }
    cin >> a >> b >> c;
    for (int i = k + 1; i <= m; i++) {
        x[i] = (a * x[i - 2] + b * x[i - 1] + c) % n + 1;
    }

    for (int i = 1; i <= k; i++) {
        cin >> y[i];
    }
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= m; i++) {
        y[i] = (a * y[i - 2] + b * y[i - 1] + c) % d + 1;
    }

    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        hull[i] = NULL;
        events[i].clear();
    }

    for (int i = 2; i <= n; i++) {
        adj[p[i]].push_back({i, l[i]});
    }
    for (int i = 1; i <= m; i++) {
        events[x[i]].push_back(y[i]);
    }

    lv[1] = 0;
    res = 1;
    dfs(1);
    cout << res << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}