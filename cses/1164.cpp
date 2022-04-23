#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &u : a) cin >> u.first >> u.second;
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int u, int v) {
        return a[u] < a[v];
    });
    set<pair<int, int>> s;
    vector<int> res(n, 0);
    for (int i = 0; i < n; i++) {
        int l = a[id[i]].first;
        int r = a[id[i]].second;
        auto it = s.lower_bound({l, -1});
        if (it == s.begin()) {
            res[id[i]] = s.size();
            s.insert({r, s.size()});
        } else {
            it--;
            res[id[i]] = it->second;
            s.erase(it);
            s.insert({r, res[id[i]]});
        }
    }
    cout << s.size() << '\n';
    for (int i = 0; i < n; i++) cout << res[i] + 1 << ' ';
        cout << '\n';
    return 0;
}