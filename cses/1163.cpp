#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int x, n;
    cin >> x >> n;
    set<int> s;   
    multiset<int> segments;
    s.insert(0);
    s.insert(x);
    segments.insert(x);
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        auto r = s.upper_bound(u);
        auto l = r;
        l--;
        segments.erase(segments.find(*r - *l));
        segments.insert(*r - u);
        segments.insert(u - *l);
        s.insert(u);
        cout << *segments.rbegin() << ' ';
    }
    cout << '\n';
    return 0;
}