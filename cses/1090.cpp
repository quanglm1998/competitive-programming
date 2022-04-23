#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int x, n;
    cin >> n >> x;
    multiset<int> s;
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        s.insert(u);
    }
    int res = 0;
    while (!s.empty()) {
        res++;
        int u = *s.rbegin();
        s.erase(s.find(u));
        auto it = s.upper_bound(x - u);
        if (it == s.begin()) continue;
        it--;
        s.erase(it);
    }
    cout << res << endl;
    return 0;
}