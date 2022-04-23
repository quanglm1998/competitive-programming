#include <bits/stdc++.h>

using namespace std;

#define int long long

// const long long INF = 1e18;
const int N = 1000010;
const int MOD = 1000000007;

int n, m, e, k;
int x[N], y[N], id[N], w[N];
int curWeight[N];
multiset<int> red, blue[2][N];
multiset<int> secondBlue;

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n >> m >> e >> k;
    int a, b, c;

    for (int i = 0; i < k; i++) {
        cin >> x[i];
    }
    cin >> a >> b >> c;
    for (int i = k; i < n; i++) {
        x[i] = (a * x[i - 2] + b * x[i - 1] + c) % m;
    }

    for (int i = 0; i < k; i++) {
        cin >> y[i];
    }
    cin >> a >> b >> c;
    for (int i = k; i < n; i++) {
        y[i] = (a * y[i - 2] + b * y[i - 1] + c) % m;
    }

    for (int i = 0; i < k; i++) {
        cin >> id[i];
    }
    cin >> a >> b >> c;
    for (int i = k; i < e; i++) {
        id[i] = (a * id[i - 2] + b * id[i - 1] + c) % (n * m + n);
    }

    for (int i = 0; i < k; i++) {
        cin >> w[i];
    }
    cin >> a >> b >> c;
    for (int i = k; i < e; i++) {
        w[i] = (a * w[i - 2] + b * w[i - 1] + c) % 1000000000;
    }


    for (int i = 0; i < n; i++) {
        if (x[i] > y[i]) swap(x[i], y[i]);
    }

    red.clear();
    for (int i = 0; i < n; i++) {
        blue[0][i].clear();
        blue[1][i].clear();
    }
    secondBlue.clear();

    int sumWeight = n * m + n;
    int sumFirstBlue = 0;
    for (int i = 0; i < n * m + n; i++) {
        curWeight[i] = 1;
    }

    auto getMax = [&](const multiset<long long> &u) -> long long {
        if (u.empty()) return 0;
        return *u.rbegin();
    };

    auto addBlue = [&](int u) {
        int foo = getMax(blue[0][u]);
        int bar = getMax(blue[1][u]);
        if (foo < bar) swap(foo, bar);
        sumFirstBlue += foo;
        secondBlue.insert(bar);
    };

    auto eraseBlue = [&](int u) {
        int foo = getMax(blue[0][u]);
        int bar = getMax(blue[1][u]);
        if (foo < bar) swap(foo, bar);
        sumFirstBlue -= foo;
        secondBlue.erase(secondBlue.find(bar));
    };

    for (int i = 0; i < n; i++) {
        red.insert(1);
        for (int j = 0; j < m; j++) {
            if (j >= x[i] && j < y[i]) {
                blue[0][i].insert(1);
            } else {
                blue[1][i].insert(1);
            }
        }
        addBlue(i);
    }

    int res = 1;

    for (int i = 0; i < e; i++) {
        if (id[i] >= n * m) { // red
            sumWeight -= curWeight[id[i]];
            sumWeight += w[i];

            red.erase(red.find(curWeight[id[i]]));
            curWeight[id[i]] = w[i];
            red.insert(w[i]);
        } else { // blue
            sumWeight -= curWeight[id[i]];
            sumWeight += w[i];

            int u = id[i] / m;
            eraseBlue(u);

            int realId = id[i] % m;
            int belong = !(realId >= x[u] && realId < y[u]);
            blue[belong][u].erase(blue[belong][u].find(curWeight[id[i]]));
            curWeight[id[i]] = w[i];
            blue[belong][u].insert(w[i]);

            addBlue(u);
        }

        int now = 0;
        now = getMax(red) + sumFirstBlue;
        if (getMax(secondBlue) != 0) {
            now = max(now, sumFirstBlue + getMax(secondBlue));
        }
        now = sumWeight - now;
        now %= MOD;
        res = (1ll * res * now) % MOD;
    }

    cout << res << '\n';
}           

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
        cerr << "Done " << test << endl;
    }
    return 0;
}