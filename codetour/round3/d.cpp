#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m;
int a[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }
    int maxVal = *max_element(a + 1, a + n);
    const int INF = 2e9;
    int res = INF;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (v * 2 >= maxVal) {
            res = min(res, u);
        }
    }
    if (res == INF) {
        cout << "impossible" << endl;
    } else {
        cout << 1ll * res * (n - 1) * 2 << endl;
    }
    return 0;
}