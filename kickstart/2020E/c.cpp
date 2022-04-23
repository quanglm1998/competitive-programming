#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
int e[N], r[N];
pair<int, int> a[N];

struct BIT {
    long long t[N];

    void init() {
        memset(t, 0, sizeof t);
    }

    void add(int x, int v) {
        while (x < N) {
            t[x] += v;
            x += x & -x;
        }
    }

    long long get(int x) {
        long long res = 0;
        while (x) {
            res += t[x];
            x -= x & -x;
        }
        return res;
    }
} t;

void solve(int test) {
    cout << "Case #" << test << ": ";
    t.init();
    cin >> n;
    long long sumE = 0;
    for (int i = 1; i <= n; i++) {
        cin >> e[i] >> r[i];
        a[i] = {e[i] + r[i], e[i]};
        sumE += e[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = n; i > 0; i--) {
        if (sumE >= a[i].first) {
            cout << n - i << ' ' << "INDEFINITELY\n";
            return;
        }
        sumE -= a[i].second;
    }

    for (int i = 1; i <= n; i++) t.add(i, e[i]);
    set<pair<int, int>> sSum;
    set<int> sBad;
    sumE = 0;
    for (int i = 1; i <= n; i++) {
        sSum.insert({e[i] + r[i], i});
        sumE += e[i];
    }

    pair<long long, int> res = {-1, -n - 1};

    for (int i = 1; i <= n; i++) {
        while (!sSum.empty() && sSum.rbegin()->first > sumE) {
            auto u = *sSum.rbegin();
            sSum.erase(u);
            sBad.insert(u.second);
        }   

        int u = *sBad.begin();
        sBad.erase(u);

        long long now = sumE + t.get(u - 1);
        res = max(res, {now, 1 - i});

        t.add(u, -e[u]);
        sumE -= e[u];
    }
    cout << -res.second << ' ' << res.first << '\n';
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