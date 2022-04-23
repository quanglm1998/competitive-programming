#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    multiset<int> s;
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        s.insert(u);
    }   
    for (int i = 1; i <= m; i++) {
        int u; cin >> u;
        auto it = s.upper_bound(u);
        if (it == s.begin()) cout << -1 << '\n';
        else {
            it--;
            cout << *it << '\n';
            s.erase(it);
        }
    }
    return 0;
}