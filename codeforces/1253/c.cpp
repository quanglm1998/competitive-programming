#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
int a[N];
long long sum[N], dp[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
        if (i < m) {
            dp[i] = sum[i];
        } else {
            dp[i] = dp[i - m] + sum[i];
        }
        cout << dp[i] << ' ';
    }
    cout << endl;
    return 0;
}