#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> vals;
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        if (u) vals.push_back(i);
    }
    int res = INF;
    for (int i = 2; i <= n; i++) {
        if (vals.size() % i) continue;
        int now = 0;
        for (int j = 0; j < vals.size(); j += i) {
            for (int k = j; k < j + i; k++) {
                now += vals[k] - vals[j];
            }
        }
        res = min(res, now);
    }
    if (res == INF) cout << -1 << endl;
    else cout << res << endl;
    return 0;
}