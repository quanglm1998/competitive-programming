#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const int VAL = 127510;

int MOD;

inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

int n, k;
int f[N][VAL];
int res[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k >> MOD;
    f[0][0] = 1;
    int maxVal = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = maxVal; j >= 0; j--) {
            if (!f[i - 1][j]) continue;
            for (int num = 0, cur = 0; cur + j < VAL && num <= k; num++, cur += i) {
                addTo(f[i][j + cur], f[i - 1][j]);
            }
        }
        maxVal = min(VAL - 1, maxVal + k * i);
    }
    for (int i = 1; i <= n; i++) {
        if (i + i > n + 1) {
            res[i] = res[n - i + 1];
            continue;
        }
        for (int j = 1; j <= maxVal; j++) {
            addTo(res[i], mul(f[i - 1][j], f[n - i][j]));
        }
        mulTo(res[i], k + 1);
        addTo(res[i], k);
    }
    for (int i = 1; i <= n; i++) cout << res[i] << '\n';
    return 0;
}