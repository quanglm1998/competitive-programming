#include <bits/stdc++.h>

using namespace std;

const int N = 800010;

int n;
pair<int, int> a[N];
vector<int> vals;

struct IT {
    pair<int, int> minVal[N << 2];
    int t[N << 2];

    void init(int node, int l, int r) {
        minVal[node] = {0, r - l + 1};
        t[node] = 0;
        if (l < r) {
            int m = l + r >> 1;
            init(node << 1, l, m);
            init(node << 1 | 1, m + 1, r);
        }
    }

    pair<int, int> join(pair<int, int> u, pair<int, int> v) {
        if (u.first > v.first) swap(u, v);
        if (u.first == v.first) u.second += v.second;
        return u;
    }

    void add(int node, int l, int r, int x, int y) {    
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            t[node]++;
            minVal[node].first++;
            return;
        }
        int m = l + r >> 1;
        add(node << 1, l, m, x, y);
        add(node << 1 | 1, m + 1, r, x, y);
        minVal[node] = join(minVal[node << 1], minVal[node << 1 | 1]);
        minVal[node].first += t[node];
    }

    pair<int, int> get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return {1e9, 0};
        if (x <= l && r <= y) {
            return minVal[node];
        }
        int m = l + r >> 1;
        pair<int, int> p1 = get(node << 1, l, m, x, y);
        pair<int, int> p2 = get(node << 1 | 1, m + 1, r, x, y);
        pair<int, int> res = join(p1, p2);
        res.first += t[node];
        return res;
    }
} it;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        vals.clear();
        for (int i = 1; i <= n; i++) {
            cin >> a[i].first >> a[i].second;
            a[i].first *= 2;
            a[i].second *= 2;
            vals.push_back(a[i].first);
            vals.push_back(a[i].second);
            vals.push_back(a[i].first + 1);
            vals.push_back(a[i].second + 1);
        }
        sort(vals.begin(), vals.end());
        vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
        sort(a + 1, a + n + 1);
        it.init(1, 0, vals.size() - 1);
        int maxVal = -1;
        int num = 0;
        for (int i = 1; i <= n; i++) {
            a[i].first = lower_bound(vals.begin(), vals.end(), a[i].first) - vals.begin();
            a[i].second = lower_bound(vals.begin(), vals.end(), a[i].second) - vals.begin();
            it.add(1, 0, vals.size() - 1, a[i].first, a[i].second);
            if (a[i].first <= maxVal) {
                maxVal = max(maxVal, a[i].second);
            } else {
                maxVal = a[i].second;
                num++;
            }
        }
        if (num == n) {
            cout << num - 1 << '\n';
            continue;
        }
        int res = 0;
        for (int i = 1; i <= n; i++) {
            pair<int, int> now = it.get(1, 0, vals.size() - 1, a[i].first + 1, a[i].second - 1);
            if (now.first > 1) continue;
            int cur = now.second;
            pair<int, int> foo = it.get(1, 0, vals.size() - 1, a[i].first, a[i].first);
            if (foo.first == 1) cur--;
            foo = it.get(1, 0, vals.size() - 1, a[i].second, a[i].second);
            if (foo.first == 1) cur--;
            res = max(res, cur);
        }
        cout << res + num << '\n';
    }   
    return 0;
}