#include <bits/stdc++.h>

using namespace std;

const int N = 25;

int n;
int a[N * 2];
int dp[2][1 << N];
int b[N * 2];

void solve(int id, int output = 0) {
    cnt = 0;
    int root = (1 << n - 1) - 1;
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i < n * 2; i++) {
        if (i == id) continue;
        if (cnt < n - 1) sum1 += a[i];
        else sum2 += a[i];
        b[cnt++] = a[i];
    }

    for (int mask = 1; mask < root; mask++) {
        int u = __builtin_ctz(mask);
        dp[0][mask] = dp[0][mask ^ (1 << u)] + b[u];
    }
    for (int mask = 1; mask < root; mask++) {
        int u = __builtin_ctz(mask);
        dp[1][mask] = dp[1][mask ^ (1 << u)] + b[u + (n - 1)];
    }
    int res = 1e9;
    int minMask = 0;
    for (int mask = 0; mask < root; mask++) {
        int tot1 = dp[0][mask] + sum2 - dp[1][mask];
        int tot2 = sum1 - dp[0][mask] + dp[1][mask];
        if (res > max(tot1, tot2)) {
            res = max(tot1, tot2);
            minMask = 0;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n * 2; i++) cin >> a[i];
    sort(a, a + n * 2);
    int res = 1e9;
    int minId = 1;
    for (int i = 1; i < n * 2; i++) {
        int foo = solve(i, 0) + a[0] + a[i];
        if (res > foo) {
            res = foo;
            minId = i;
        }
    }
    solve(minId, 1);
    return 0;
}