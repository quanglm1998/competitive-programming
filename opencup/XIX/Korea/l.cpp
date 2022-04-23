#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
int a[N];
int nxt[N];
pair<int, int> res[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    nxt[n] = n;
    for (int i = n - 1; i >= 1; i--) {
        nxt[i] = i + 1;
        if (i + 2 <= n && (a[i] <= a[i + 1]) == (a[i + 1] <= a[i + 2])) {
            nxt[i] = nxt[i + 1];
        }
    }
    for (int i = 2; i <= n; i++) {
        int cur = 1;
        while (cur <= n) {
            res[i].first++;
            int now = min(n, max(cur + i - 1, nxt[cur]));
            if (now > nxt[cur]) res[i].second += now - nxt[cur];
            cur = now + 1;
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int u; cin >> u;
        cout << res[u].first << ' ' << res[u].second << '\n';
    }
    return 0;
}