#include <bits/stdc++.h>

using namespace std;

const int N = 510;

int n, k;
bool dp[N][N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] ^= dp[i - 1][j];
            if (i > 1) {
                for (int c = 1; c < i; c++) if (j - 2 * i + 2 * c + 1 >= 0) {
                    dp[i][j] ^= dp[i - 2][j - 2 * i + 2 * c + 1];
                }
            }
        }   
    }   
    cout << dp[n][k] << endl;
    return 0;
}