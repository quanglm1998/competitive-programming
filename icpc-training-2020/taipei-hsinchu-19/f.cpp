#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;
const int NUM = 13;
const long long INF = 1e18;

int n;
long long k;
pair<long long, int> a[N];
long long f[2][NUM][1 << NUM];
unordered_map<long long, int> cntId;
int numMask[1 << NUM];
long long val[1 << NUM];

vector<long long> getDivs(long long u) {
    vector<long long> res;
    for (int i = 2; 1ll * i * i <= u; i++) {
        if (u % i == 0) {
            res.push_back(i);
            while (u % i == 0) u /= i;
        }
    }
    if (u > 1) res.push_back(u);
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    long long g = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
        g = __gcd(a[i].first, g);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i].second;
    }
    sort(a + 1, a + n + 1, [&](pair<long long, int> u, pair<long long, int> v) {
        return u.second < v.second;
    });
    if (g == 1) {
        cout << 0 << endl;
        return 0;
    }
    vector<long long> divs = getDivs(g);
    assert(divs.size() < NUM);
    int sz = divs.size();
    for (int i = 0; i <= sz; i++) {
        fill(f[0][i], f[0][i] + (1 << sz), INF);
        fill(f[1][i], f[1][i] + (1 << sz), INF);
    }
    f[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        long long foo = 1;
        for (int j = 0; j < sz; j++) {
            long long now = 1;
            while (a[i].first % divs[j] == 0) {
                now *= divs[j];
                a[i].first /= divs[j];
            }
            val[1 << j] = now;
            foo *= now;
        }
        if (cntId[foo] >= sz) continue;
        cntId[foo]++;

        // cout << "# " << i << ' ' << a[i].second << endl;
        val[0] = 1;
        for (int mask = 1; mask < (1 << sz); mask++) {
            int lastBit = 1 << __builtin_ctz(mask);
            val[mask] = val[mask ^ lastBit] * val[lastBit];
            if (val[mask] > k) continue;
            // cout << val[mask] << endl;
            if (numMask[mask] >= sz) continue;
            numMask[mask]++;

            int xorMask = ((1 << sz) - 1) ^ mask;
            for (int subMask = xorMask; ; subMask = (subMask - 1) & xorMask) {
                for (int j = 0; j < sz; j++) {
                    f[1][j + 1][mask ^ subMask] = min(f[1][j + 1][mask ^ subMask], f[0][j][subMask] + a[i].second);
                }
                if (!subMask) break;
            }
        }

        for (int i = 0; i <= sz; i++) {
            for (int j = 0; j < (1 << sz); j++) {
                f[0][i][j] = min(f[0][i][j], f[1][i][j]);
            }
        }
    }

    long long res = INF;
    for (int i = 1; i <= sz; i++) {
        res = min(res, 1ll * i * f[0][i][(1 << sz) - 1]);
        // cout << i << ' ' << f[cur][i][(1 << sz) - 1] << ' ' << f[cur ^ 1][i][(1 << sz) - 1] << endl;
    }
    if (res >= INF) cout << -1 << endl;
    else cout << res << endl;
    return 0;
}