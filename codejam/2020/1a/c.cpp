#include <bits/stdc++.h>

using namespace std;

const int X[] = {0, 1, 0, -1};
const int Y[] = {1, 0, -1, 0};

void solve(int test) {
    cout << "Case #" << test << ": ";

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m, 0));
    vector<vector<pair<int, int>>> nxt[4];
    vector<vector<bool>> used(n, vector<bool>(m, 0));

    for (int it = 0; it < 4; it++) {
        nxt[it].assign(n, vector<pair<int, int>>(m, {0, 0}));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                nxt[it][i][j] = {i + X[it], j + Y[it]};
            }
        }
    }
    
    long long sum = 0;
    for (auto &u : a) {
        for (auto &v : u) {
            cin >> v;
            sum += v;
        }
    }

    long long res = 0;
    set<pair<int, int>> need;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need.insert({i, j});
        }
    }

    auto isInside = [&](int u, int v) {
        return u >= 0 && u < n && v >= 0 && v < m;
    };

    function<pair<int, int>(int, int, int)> get = [&](int u, int v, int dir) -> pair<int, int> {
        if (!isInside(u, v)) return make_pair(u, v);
        if (!used[u][v]) return make_pair(u, v);
        pair<int, int> now = get(nxt[dir][u][v].first, nxt[dir][u][v].second, dir);
        nxt[dir][u][v] = now;
        return now;
    };

    auto canErase = [&](int u, int v) -> bool {
        vector<int> vals;
        for (int i = 0; i < 4; i++) {
            pair<int, int> cur = get(nxt[i][u][v].first, nxt[i][u][v].second, i);
            if (!isInside(cur.first, cur.second)) continue;
            vals.push_back(a[cur.first][cur.second]);
        }
        if (vals.empty()) return 0;
        return vals.size() * a[u][v] < accumulate(vals.begin(), vals.end(), 0);
    };

    while (!need.empty()) {
        vector<pair<int, int>> erased;
        res += sum;
        for (auto val : need) {
            int u, v;
            tie(u, v) = val;
            if (canErase(u, v)) {
                sum -= a[u][v];
                erased.push_back({u, v});
            }
        }

        for (auto val : erased) {
            used[val.first][val.second] = 1;
        }

        need.clear();
        for (auto val : erased) {
            for (int i = 0; i < 4; i++) {
                pair<int, int> cur = get(val.first, val.second, i);
                if (isInside(cur.first, cur.second)) need.insert(cur);
            }
        }
    }
    cout << res << '\n';
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