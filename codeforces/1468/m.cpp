#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int MAGIC = 100;

int n;
vector<int> a[N];
vector<int> b[N * 2];
vector<int> vals;
int order[N];
bool has[N];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
unordered_set<long long, custom_hash> safe_set;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vals.reserve(N * 2);
    safe_set.reserve(MAGIC * MAGIC * MAGIC);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int k;
            cin >> k;
            a[i].resize(k);
            for (auto &u : a[i]) {
                cin >> u;
                vals.push_back(u);
            }
        }
        sort(vals.begin(), vals.end());
        vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

        for (int i = 0; i < vals.size(); i++) b[i].clear();
        for (int i = 1; i <= n; i++) {
            for (int u : a[i]) {
                int v = lower_bound(vals.begin(), vals.end(), u) - vals.begin();
                b[v].push_back(i);
            }
        }

        for (int i = 0; i < vals.size(); i++) {
            sort(b[i].begin(), b[i].end());
        }

        iota(order, order + vals.size(), 0);
        sort(order, order + vals.size(), [&](int u, int v) {
            return b[u].size() > b[v].size();
        });

        pair<int, int> res(-1, -1);
        for (int id = 0; id < vals.size() && res.first == -1; id++) {
            int i = order[id];
            if (b[i].size() < MAGIC) break;
            for (int u : b[i]) has[u] = 1;

            for (int jd = i + 1; jd < vals.size() && res.first == -1; jd++) {
                int j = order[jd];
                pair<int, int> now(-1, -1);
                for (auto u : b[j]) {
                    if (has[u]) {
                        if (now.first == -1) now.first = u;
                        else if (now.second == -1) now.second = u;
                    }
                }
                if (now.second != -1) res = now;
            }

            for (int u : b[i]) has[u] = 0;
        }

        if (res.first != -1) {
            cout << res.first << ' ' << res.second << '\n';
            continue;
        }


        safe_set.clear();
        for (int id = 0; id < vals.size() && res.first == -1; id++) {
            int i = order[id];
            if (b[i].size() >= MAGIC) continue;
            for (int j = 0; j < b[i].size() && res.first == -1; j++) {
                for (int k = j + 1; k < b[i].size() && res.first == -1; k++) {
                    long long now = 1ll * b[i][j] * N + b[i][k];
                    if (safe_set.count(now)) {
                        res = {b[i][j], b[i][k]};
                    } else safe_set.insert(now);
                }
            }
        }

        if (res.first == -1) {
            cout << -1 << '\n';
        } else cout << res.first << ' ' << res.second << '\n';
    }
    return 0;
}