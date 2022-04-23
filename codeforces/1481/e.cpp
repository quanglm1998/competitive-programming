#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

int n;
int a[N];
int minVal[N], maxVal[N];
int num[N];
int pre[N];
int f[N], g[N];
int last[N];
int prePos[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    fill(minVal + 1, minVal + n + 1, n + 1);
    fill(maxVal + 1, maxVal + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        minVal[a[i]] = min(minVal[a[i]], i);
        maxVal[a[i]] = max(maxVal[a[i]], i);
        num[a[i]]++;
        prePos[i] = last[a[i]];
        last[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (maxVal[i]) {
            pre[maxVal[i]] = minVal[i];
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1];
        if (pre[i]) {
            f[i] = max(f[i], f[pre[i]] + num[a[i]]);
        }
        g[i] = 1 + f[i - 1];
        if (prePos[i]) {
            g[i] = max(g[i], 1 + g[prePos[i]]);
        }
        res = max(res, g[i]);
    }
    cout << n -  res << '\n';
    return 0;
}