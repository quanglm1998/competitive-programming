#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int M = 70;

int n;
long long a[N];
int tot[M];
int cnt[M][M];
long long p2[M];
bool dp[M][M];
int trace[M][M];
int curCnt[M];

bool check(int u, int x, int y) {
    for (int i = 0; i < M; i++) {
        curCnt[i] = cur[u][i];
    }
    if (x > y) swap(x, y);
    
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    p2[0] = 1;
    for (int i = 1; i < M; i++) p2[i] = p2[i - 1] * 2;
    while (1) {
        cin >> n;
        if (!n) break;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int maxNum3 = 0;
        for (int i = 1; i <= n; i++) {
            int num2 = 0, num3 = 0;
            int u = x[i];
            while (u % 3 == 0) {
                u /= 3;
                num3++;
            }
            while (u % 2 == 0) {
                u /= 2;
                num2++;
            }
            tot[num3 + 1]++;
            cnt[num3 + 1][num2]++;
            maxNum3 = max(maxNum3, num3 + 1);
        }

        dp[0][0] = 1;
        for (int i = 0; i < maxNum3; i++) {
            for (int j = 0; j < M; j++) {
                dp[i + 1][j] = 0;
                trace[i + 1][j] = -1;
            }
            for (int j = 0; j < M; j++) {
                if (!dp[i][j]) continue;
                for (int k = 0; k < M; k++) {
                    if (check(i, j, k)) {
                        dp[i + 1][k] = 1;
                        trace[i + 1][k] = j;
                    }
                }
            }
        }

        // reset
        for (int i = 1; i <= n; i++) {
            int num2 = 0, num3 = 0;
            int u = x[i];
            while (u % 3 == 0) {
                u /= 3;
                num3++;
            }
            while (u % 2 == 0) {
                u /= 2;
                num2++;
            }
            tot[num3 + 1]--;
            cnt[num3 + 1][num2]--;
        }
    }
    return 0;
}