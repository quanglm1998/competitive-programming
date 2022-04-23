#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

struct Tile {
    int p, h, id;
    bool operator < (const Tile &u) const {
        return p < u.p;
    }
};

int n;
Tile a[2][N];
int cur[2];
int res[2][N];

void add(multiset<pair<int, int>> &s, int it) {
    int l = cur[it];
    if (l > n) return;
    int r = l;
    while (r <= n && a[it][r].p == a[it][l].p) {
        s.insert({a[it][r].h, a[it][r].id});
        r++;
    }
    cur[it] = r;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int it = 0; it < 2; it++) {
        for (int i = 1; i <= n; i++) {
            a[it][i].id = i;
            cin >> a[it][i].p;
        }
        for (int i = 1; i <= n; i++) {
            cin >> a[it][i].h;
        }
        sort(a[it] + 1, a[it] + n + 1);
    }
    cur[0] = cur[1] = 1;
    multiset<pair<int, int>> s[2];
    int cnt = 0;
    while (1) {
        int found = 0;
        for (int it = 0; it < 2; it++) {
            if (s[it].empty()) add(s[it], it);
            if (s[it].empty()) found = 1;
        }
        if (found) break;
        if (s[0].size() > s[1].size()) {
            for (auto u : s[1]) {
                cnt++;
                auto it = s[0].lower_bound({u.first + 1, -1});
                if (it == s[0].end()) return (cout << "impossible\n", 0);
                res[1][cnt] = u.second;
                res[0][cnt] = it->second;
                s[0].erase(it);
            }
            s[1].clear();
        } else {
            for (auto u : s[0]) {
                cnt++;
                auto it = s[1].lower_bound({u.first, -1});
                if (it == s[1].begin()) return (cout << "impossible\n", 0);
                it--;
                res[0][cnt] = u.second;
                res[1][cnt] = it->second;
                s[1].erase(it);
            }
            s[0].clear();
        }
    }
    for (int it = 0; it < 2; it++) {
        for (int i = 1; i <= n; i++) cout << res[it][i] << ' ';
            cout << '\n';
    }
    return 0;
}