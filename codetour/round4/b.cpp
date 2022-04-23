#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

int n, m, s;
int a[N];
int cnt[22];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int u;
            cin >> u;
            a[i] |= (1 << u - 1);
            cnt[u - 1]++;
        }
    }
    int res = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        int mn = m;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                mn = min(mn, cnt[i]);
            }
        }
        if (mn < s) continue;
        int tot = 0;
        for (int i = 1; i <= m; i++) {
            if ((a[i] & mask) == mask) {
                tot++;
                if (tot == s) break;
            }
        }
        res += tot >= s;
    }
    cout << res << endl;
    return 0;
}