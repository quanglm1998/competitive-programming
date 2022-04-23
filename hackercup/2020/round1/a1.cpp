#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1000010;
const int MOD = 1000000007;

int n, k, w;
int l[N], h[N];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n >> k >> w;
    for (int i = 1; i <= k; i++) {
        cin >> l[i];
    }
    int a, b, c, d; 
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; i++) {
        l[i] = (1ll * a * l[i - 2] + 1ll * b * l[i - 1] + c) % d + 1;
    }
    for (int i = 1; i <= k; i++) {
        cin >> h[i];
    }
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; i++) {
        h[i] = (1ll * a * h[i - 2] + 1ll * b * h[i - 1] + c) % d + 1;
    }
    map<int, int> highest;
    int res = 1;
    int last = -1e9;
    int now = 0;

    for (int i = 1; i <= n; i++) {
        int pos = l[i];
        // if (h[i] == 0) cout << i << endl;
        // assert(h[i] > 0);
        while (highest[pos] >= h[i]) pos++;
        for (int j = pos; j < l[i] + w; j++) {
            if (highest[j] > 0) now -= 2;
            now -= abs(highest[j] - highest[j - 1]);
        }
        // cout << "# " << i << endl;
        // cout << pos << ' ' << now << endl;
        for (int j = pos; j < l[i] + w; j++) {
            highest[j] = h[i];
            now += 2;
        }
        now += h[i];
        now += abs(highest[pos] - highest[pos - 1]);
        res = 1ll * res * (now % MOD) % MOD;
        // cout << i << ' ' << now << endl;
    }
    cout << res << endl;
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