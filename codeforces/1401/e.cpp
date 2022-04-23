#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n, m;
vector<int> s[N], t[N];
pair<int, pair<int, int>> a[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int y, l, r;
        cin >> y >> l >> r;
        s[l].push_back(y);
        t[r].push_back(y);
    }
    const int MAX = 1000000;
    s[0].push_back(MAX);
    s[0].push_back(0);
    t[MAX].push_back(MAX);
    t[MAX].push_back(0);

    for (int i = 1; i <= m; i++) {
        cin >> a[i].first >> a[i].second.first >> a[i].second.second;
    }

    a[m + 1] = {0, {0, MAX}};
    a[m + 2] = {MAX, {0, MAX}};

    m += 2;

    sort(a + 1, a + m + 1, [&](pair<int, pair<int, int>> &u, pair<int, pair<int, int>> &v) {
        return u.first < v.first;
    });

    long long res = 0;

    set<int> has;

    int cur = 0;

    for (int i = 1; i <= m; i++) {
        
    }
    cout << res << '\n';
    return 0;
}