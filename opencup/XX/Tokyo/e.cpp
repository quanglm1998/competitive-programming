#include <bits/stdc++.h>

using namespace std;

const int K = 220;
const int LOG = 60;
const int LOGA = 17;

int getBit(long long u, int id) {
    return u >> id & 1;
}

long long n, s;
int k;
int a[K];
bool dp[LOG + 1][1 << LOGA];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> s >> k;
        for (int i = 1; i <= k; i++) {
            cin >> a[i];
        }
        dp[0][0] = 1;
        for (int i = 0; i < LOG; i++) {
            fill(dp[i + 1], dp[i + 1] + (1 << LOGA), 0);
            for (int j = 0; j < 1 << LOGA; j++) {
                if (!dp[i][j]) continue;
                if (n >> i & 1) {
                    for (int id = 1; id <= k; id++) {
                        if (getBit(s, i) == getBit(j + a[id], 0)) dp[i + 1][(j + a[id]) >> 1] ^= 1;
                    }
                } else {
                    if (getBit(j, 0) == getBit(s, i)) dp[i + 1][j >> 1] ^= 1;
                }
            }
        }
        cout << dp[LOG][0] << '\n';
    }
    return 0;
}