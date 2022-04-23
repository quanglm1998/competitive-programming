#include <bits/stdc++.h>

using namespace std;

const int N = 10010;

int n;
int a[N];
int dp[N][4];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            dp[i][j] = 1e9;
        }
        if (i == 1) {
            for (int j = 0; j < 4; j++) {
                dp[i][j] = 0;
            }
        } else {
            int sign = (a[i - 1] < a[i] ? -1 : a[i - 1] == a[i] ? 0 : 1);
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    int now = k < j ? -1 : k == j ? 0 : 1;
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + (sign != now));
                }
            }
        }
    }
    cout << *min_element(dp[n], dp[n] + 4) << '\n';
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