#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n;
char s[N];
int cnt[4][N];

int get(int u, int c) {
    if (cnt[c][n] <= n / 4) return 0;
    int need = cnt[c][n] - n / 4;
    int low = u - 1;
    int high = n + 1;
    while (high - low > 1) {
        int mid = low + high >> 1;
        int tot = cnt[c][mid] - cnt[c][u - 1];
        if (tot >= need) high = mid;
        else low = mid;
    }
    return high;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            cnt[j][i] += cnt[j][i - 1];
        }
        if (s[i] == 't') cnt[0][i]++;
        else if (s[i] == 'd') cnt[1][i]++;
        else if (s[i] == 'h') cnt[2][i]++;
        else if (s[i] == 'p') cnt[3][i]++;
    }
    int ans = n;
    for (int i = 1; i <= n; i++) {
        int res = 0;
        for (int j = 0; j < 4; j++) {
            res = max(res, get(i, j));
        }
        if (res <= n) {
            ans = min(ans, max(0, res - i + 1));
        }
    }
    cout << ans << endl;
    return 0;
}