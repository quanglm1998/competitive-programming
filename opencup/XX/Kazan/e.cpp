#include <bits/stdc++.h>

using namespace std;

const int N = 64;
const int LOG = 60;

int n, q;
bitset<N + LOG> basis[N + LOG];
int cost[N + LOG];

void add(bitset<N + LOG> now, int w) {
    for (int i = 0; i < N + LOG; i++) {
        if (!now[i]) continue;
        if (!basis[i][i]) {
            basis[i] = now;
            cost[i] = w;
            return;
        }
        if (cost[i] < w) {
            swap(cost[i], w);
            swap(basis[i], now);
        }
        now ^= basis[i];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    long long res = 0;
    while (q--) {
        int u, v, w;
        long long a;
        cin >> u >> v >> a >> w;
        bitset<N + LOG> now = a;
        now[LOG + u - 1] = 1;
        now[LOG + v - 1] = 1;
        add(now, w);
        long long res = accumulate(cost, cost + N + LOG, 0LL);
        cout << res << '\n';
    }
    return 0;
}