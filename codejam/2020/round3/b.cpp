#include <bits/stdc++.h>

using namespace std;
#define int long long

const int N = 510;

int n, k;
int x[N], t[N];
bool isGood[N];
int lastPos[N];
pair<int, int> lastRange[N];
int dp[N][N];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> k >> n;

    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    fill(isGood, isGood + n * 3 + 1, 0);
    fill(lastPos, lastPos + n * 3 + 1, 0);
    for (int i = 1; i <= n * 3; i++) {
        fill(dp[i], dp[i] + n * 3 + 1, 1e9);
    }

    x[0] = x[1] + x[n] - k;
    for (int i = n + 1; i <= n * 3 + 1; i++) {
        x[i] = x[i - n] + k;
    }
    for (int i = 1; i < n * 3; i++) {
        isGood[i] = (x[i + 1] - x[i]) > (x[i] - x[i - 1]) && (x[i + 1] - x[i]) >= (x[i + 2] - x[i + 1]);
    }
    for (int i = 1; i <= n * 2; i++) {
        pair<long long, long long> now(x[i], x[i + 1]);
        lastRange[i] = now;
        pair<long long, long long> cur = now;
        for (int j = 1; j <= n * 2 && i + j <= n * 2; j++) {
            if (j & 1) {
                cur.first = cur.second - x[i + j + 1] + x[i + j];
            } else {
                cur.second = cur.first + x[i + j + 1] - x[i + j];
            }
            now.first = max(now.first, cur.first);
            now.second = min(now.second, cur.second);
            if (now.first >= now.second) {
                lastPos[i] = i + j - 1;
                break;
            }
            if (j <= n) lastRange[i] = now;
        }
        if (lastPos[i] == 0) lastPos[i] = n * 2;
    }

    //whole
    if (lastPos[1] > n) {
        int sum = 0;
        for (int i = 2; i <= n; i++) {
            sum = x[i] * 2 - sum; 
        }
        sum = x[n + 1] - sum;
        sum += x[1];
        if (n % 2 == 0) {
            if (sum == 0) {
                cout << n << '\n';
                return;
            }
        } else {
            if (sum >= lastRange[1].first * 2 && sum <= lastRange[1].second * 2) {
                cout << n << '\n';
                return;
            }
        }
    }

    for (int len = 1; len <= n + 1; len++) {
        for (int i = 1; i + len - 1 <= n * 2; i++) {
            int j = i + len - 1;
            if (!isGood[i]) continue;
            if (!isGood[j]) continue;

            if (lastPos[i] >= j) dp[i][j] = len;

            for (int k = i + 1; k < j; k++) {
                if (!isGood[k]) continue;
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    int res = 1e9;
    for (int i = 1; i <= n; i++) {
        if (isGood[i]) {
            res = min(res, dp[i][i + n]);
        }
    }
    cout << res << '\n';
    return;
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}