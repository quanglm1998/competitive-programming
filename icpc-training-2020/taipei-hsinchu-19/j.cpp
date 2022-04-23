#include <bits/stdc++.h>

using namespace std;

const int N = 510;
const int M = 20;

int n, m;
bitset<N> a[M];
int res = 0;

void solve(int u, int numBit, bitset<N> mask) {
    if (numBit >= res) return;
    if (mask.count() == n) {
        res = numBit;
        return;
    }
    if (u == m + 1) return;
    solve(u + 1, numBit + 1, mask | a[u]);
    solve(u + 1, numBit, mask);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            string u;
            cin >> u;
            a[i] = bitset<N>(u);
        }
        sort(a + 1, a + m + 1, [&](bitset<N> &u, bitset<N> &v) {
            return u.count() > v.count();
        });
        res = m + 1;
        bitset<N> cur = 0;
        solve(1, 0, cur);
        if (res > m) cout << -1 << endl;
        else cout << res << endl;
    }
    return 0;
}