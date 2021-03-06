#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int N = 3010;

inline int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int sub(int u, int v) {
    return (u -= v) < 0 ? u + MOD : u;
}

inline int mul(int u, int v) {
    return (long long)u * v % MOD;
}

inline int power(int u, int v) {
    int res = 1;
    while (v) {
        if (v & 1) res = mul(res, u);
        u = mul(u, u);
        v >>= 1;
    }
    return res;
}

inline int inv(int u) {
    return power(u, MOD - 2);
}

int n, m;
char s[N], t[N];
int dp[N][N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> (s + 1);
    cin >> (t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);
    for (int i = 1; i <= m + 1; i++) {
        dp[0][i] = 1;
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i] == t[j]) {
                dp[i][j] = add(dp[i][j], dp[i - 1][j + 1]);
            }
            if (j + i - 1 > m || s[i] == t[j + i - 1]) {
                dp[i][j] = add(dp[i][j], dp[i - 1][j]);
            }
        }
        dp[i][m + 1] = mul(dp[i - 1][m + 1], 2);
        if (i >= m) {
            res = add(res, dp[i][1]);   
        }
    }
    cout << res << endl;
    return 0;
}