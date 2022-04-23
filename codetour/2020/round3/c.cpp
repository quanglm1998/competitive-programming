#include <bits/stdc++.h>

using namespace std;

const int N = 210;
const int MOD = 1000000007;

inline int add(int u, int v, int mod = MOD) {return (u += v) >= mod ? u - mod : u;}
inline int sub(int u, int v, int mod = MOD) {return (u -= v) < 0 ? u + mod : u;}
inline int mul(int u, int v, int mod = MOD) {return (long long)u * v % mod;}
inline int power(int u, int v, int mod = MOD) {int res = 1;for (; v; v >>= 1, u = mul(u, u, mod)) if (v & 1) res = mul(res, u, mod); return res;}
inline int inv(int u, int mod = MOD) {return power(u, mod - 2, mod);}
inline void addTo(int &u, int v, int mod = MOD) {u = add(u, v, mod);}
inline void subTo(int &u, int v, int mod = MOD) {u = sub(u, v, mod);}
inline void mulTo(int &u, int v, int mod = MOD) {u = mul(u, v, mod);}

int n;
char s[N];
int cnt[2][N][N];
int dp[N][N];
int minVal[N][N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    cin >> (s + 1);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < i; j++) dp[i][j] = 1;
    }
    for (int l = n; l; l--) {
        for (int r = l; r <= n; r++) {
            if (l == r) {
                dp[l][r] = 1;
                cnt[0][l][r] = (s[l] == 'B');
                cnt[1][l][r] = (s[l] == 'W');
                minVal[l][r] = 0;
            } else {
                cnt[0][l][r] = cnt[0][l][r - 1] + cnt[0][r][r];
                cnt[1][l][r] = cnt[1][l][r - 1] + cnt[1][r][r];
                minVal[l][r] = min(cnt[0][l][r], cnt[1][l][r]);
                dp[l][r] = 0;
                for (int k = l; k < r; k++) {
                    if (s[r] != s[k]) {
                        int now = minVal[l][k - 1] + minVal[k + 1][r - 1];
                        if (now + 1 == minVal[l][r]) {
                            addTo(dp[l][r], mul(dp[l][k - 1], dp[k + 1][r - 1]));
                        }
                    }
                }
                if (minVal[l][r] == minVal[l][r - 1]) {
                    addTo(dp[l][r], dp[l][r - 1]);
                }
            }
            // cout << l << ' ' << r << ' ' << dp[l][r] << endl;
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}