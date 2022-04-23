#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &u : a) cin >> u.first >> u.second;
    sort(a.begin(), a.end());
    multiset<int> s;
    int res = 0;
    for (int i = 0; i < a.size(); i++) {
        while (!s.empty() && *s.begin() < a[i].first) s.erase(s.begin());
        res = max(res, 1 + (int)s.size());
        s.insert(a[i].second);
    }
    cout << res << '\n';
    return 0;
}