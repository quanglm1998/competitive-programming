#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for (auto &u : a) cin >> u.first >> u.second;
    sort(a.begin(), a.end());
    multiset<int> s;
    for (int i = 1; i <= k; i++) s.insert(0);
    int res = 0;
    for (auto u : a) {
        auto it = s.upper_bound(u.first);
        if (it == s.begin()) {
            if (u.second < *s.rbegin()) {
                s.erase(s.find(*s.rbegin()));
                s.insert(u.second);
            }
        } else {
            res++;
            it--;
            s.erase(it);
            s.insert(u.second);
        }
    }
    cout << res << endl;
    return 0;
}