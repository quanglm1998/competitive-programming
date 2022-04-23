#include <bits/stdc++.h>

using namespace std;

const int N = 8010;

int n;
long double p;
long double dp[N][N];

void solve(int test) {
    cout << "Case #" << test << ":\n";
    cin >> n;
    cin >> p;
    dp[2][1] = dp[2][2] = 1.0;
    for (int i = 3; i <= n; i++) {
        int delta = i * (i - 1) / 2;
        for (int j = 1; j <= i; j++) {
            dp[i][j] = 1.0;
            if (j > 1) {
                long double now = p * (j - 1) * (i - j + 1) + (j - 1) * (j - 2) / 2;
                dp[i][j] += now / delta * dp[i - 1][j - 1];
            }
            if (j < i) {
                long double now = (1.0 - p) * j * (i - j) + (i - j) * (i - j - 1) / 2;
                // cout << now << ' ' << delta << endl;
                dp[i][j] += now /delta * dp[i - 1][j];
            }
            // cout << i << ' ' << j << ' ' << fixed << setprecision(10) << dp[i][j] << endl;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << fixed << setprecision(10) << dp[n][i] << '\n';
    }

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}