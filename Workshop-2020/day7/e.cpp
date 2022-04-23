#include <bits/stdc++.h>

using namespace std;

const int N = 200020;

#define int long long

int n;

struct Point {
    int t, x, y;
} a[N];

multiset<int> val;
set<pair<int, int>> s;

int get() {
    if (s.empty()) return -1;
    if (s.begin()->first != 0) return -1;
    if (s.rbegin()->second != 0) return -1;
    if (s.size() == 1) return 0;
    return *val.rbegin();
}

void erase(pair<int, int> u) {
    auto it = s.lower_bound(u);
    // cout << "before " << s.size() << endl;
    assert(s.count(u));
    s.erase(it);
    // cout << "after " << s.size() << endl;
    it = s.lower_bound(u);
    if (it != s.end()) {
        int now = u.second + it->first;
        val.erase(val.find(now));
    }
    if (it != s.begin()) {
        it--;
        int now = it->second + u.first;
        val.erase(val.find(now));
    }
    auto r = s.lower_bound(u);
    if (r != s.end() && r != s.begin()) {
        auto l = r;
        l--;
        int now = l->second + r->first;
        val.insert(now);
    }
}

void insert(pair<int, int> u) {
    auto r = s.lower_bound(u);
    if (r != s.end() && r != s.begin()) {
        auto l = r;
        l--;
        int now = l->second + r->first;
        val.erase(val.find(now));
    }
    auto it = s.lower_bound(u);
    if (it != s.end()) {
        int now = u.second + it->first;
        val.insert(now);
    }
    if (it != s.begin()) {
        it--;
        int now = it->second + u.first;
        val.insert(now);
    }
    s.insert(u);
}

void update(pair<int, int> p) {
    while (!s.empty()) {
        auto it = s.lower_bound({p.first, -1});
        if (it == s.end()) break;
        if (it->second >= p.second) erase(*it);
        else break;
    }
    if (s.empty()) {
        insert(p);
        return;
    }
    auto it = s.lower_bound({p.first + 1, -1});
    if (it != s.begin()) {
        it--;
        if (p.second >= it->second) return;
    }
    insert(p);
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].t >> a[i].x >> a[i].y;
    }
    sort(a + 1, a + n + 1, [&](Point &u, Point &v) {
        return u.t < v.t;
    });
    int res = 0;
    for (int l = 1, r = 1; l <= n; l = r) {
        while (r <= n && a[l].t == a[r].t) r++;
        // cout << "# " << l << endl;
        // cout << get() << endl;
        if (a[l].t) {
            int foo = get();
            if (foo == -1) {
                cout << "Infinity" << endl;
                return 0;
            }
            if (foo) res = max(res, foo - 2 + a[l].t - 1);
        }
        for (int i = l; i < r; i++) {
            update({a[i].x, a[i].y});
        }
    }
    int foo = get();
    if (foo != 0) cout << "Infinity" << endl;
    else cout << res << endl;
    return 0;
}