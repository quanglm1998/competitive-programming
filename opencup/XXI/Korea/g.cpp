#include <bits/stdc++.h>

using namespace std;

const int N = 50010;
const int MOD = (int)1e9 + 7;
const int K = 3;

inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

int n, k;
char s[N];
int dp[2][K + 1][1 << 2 * K];
vector<int> foo, bar;

inline int getBit(int mask, int u) {
    return mask >> u & 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> (s + 1);
    n = strlen(s + 1);
    cin >> k;
    int cur = 0;
    dp[cur][0][0] = 1;
    foo.assign(k * 2 + 2, 0);
    bar.assign(k * 2 + 2, 0);
    for (int i = 1; i <= n; i++, cur ^= 1) {
        for (int j = 0; j <= k; j++) fill(dp[cur ^ 1][j], dp[cur ^ 1][j] + (1 << 2 * k), 0);

        for (int mask = 0; mask < (1 << 2 * k); mask++) {

            // vector<int> foo(k * 2 + 2);
            foo[0] = 0;
            for (int ii = 0; ii < 2 * k; ii++) {
                foo[ii + 1] = foo[ii] + getBit(mask, ii);
            }
            foo[k * 2 + 1] = foo[k * 2];

            vector<char> ss;
            for (int ii = 0; ii <= k * 2; ii++) {
                int realId = i + ii - k;
                if (realId >= 1 && realId <= n) ss.push_back(s[realId]);
            }
            sort(ss.begin(), ss.end());
            ss.resize(unique(ss.begin(), ss.end()) - ss.begin());
            ss.push_back('*');

            for (char ch : ss) {
                // vector<int> bar = foo;
                for (int ii = 0; ii < bar.size(); ii++) bar[ii] = foo[ii];

                for (int ii = 0; ii <= k * 2 + 1; ii++) {
                    if (ii > 0) bar[ii] = max(bar[ii], bar[ii - 1]);
                    if (ii < k * 2 + 1) {
                        int realId = i + ii - k;
                        if (realId >= 1 && realId <= n && s[realId] == ch) {
                            bar[ii + 1] = max(bar[ii + 1], foo[ii] + 1);
                        }
                    }
                }
                // bar.erase(bar.begin());
                int nxtMask = 0;
                for (int i = 1; i + 1 < bar.size(); i++) {
                    nxtMask |= (bar[i + 1] - bar[i] << i - 1);
                }
                for (int j = 0; j <= k; j++) {
                    if (!dp[cur][j][mask]) continue;
                    int now = dp[cur][j][mask];
                    if (ch == '*') mulTo(now, 26 - (ss.size() - 1));
                    int target = j - (bar[k + 1] - foo[k] - 1);
                    if (target >= 0 && target <= k) {
                        addTo(dp[cur ^ 1][target][nxtMask], now);
                    }
                }
            }
        }
    }

    int res = 0;
    for (int j = 0; j <= k; j++) {
        for (int mask = 0; mask < (1 << 2 * k); mask++) {
            addTo(res, dp[cur][j][mask]);
        }
    }
    cout << res << endl;
    return 0;
}