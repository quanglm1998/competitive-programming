#include <bits/stdc++.h>

using namespace std;

map<long long, int> m;
pair<int, int> res[200];
int cnt;

int solve(long long u) {
    if (m.count(u)) return m[u];
    int l = -1, r = -1; 
    if (u > 1) {
        l = solve((u + 1) / 2);
        r = solve(u / 2);
    }
    res[cnt] = {l, r};
    return m[u] = cnt++;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        m.clear();
        cnt = 0;
        solve(n);
        cout << cnt << '\n';
        for (int i = 0; i < cnt; i++) cout << res[i].first << ' ' << res[i].second << '\n';
        cout << cnt - 1 << '\n';
    }
    return 0;
}