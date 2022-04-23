#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int m, n, q;
string a[N];

int goDown(int u, int v) {
    if (v == -1) return -1;
    if (a[u][v] == '/') {
        if (v > 0 && a[u][v - 1] == '/') return v - 1;
        return -1;
    } else {
        if (v + 1 < n && a[u][v + 1] == '\\') return v + 1;
        return -1;
    }
}

int goUp(int u, int v) {
    if (v == -1) return -1;
    if (a[u][v] == '/') {
        if (v + 1 < n && a[u][v + 1] == '/') return v + 1;
        return -1;
    } else {
        if (v > 0 && a[u][v - 1] == '\\') return v - 1;
        return -1;
    }
}

struct IT {
    vector<int> down[N << 2], up[N << 2];

    void init(int node, int l, int r) {
        up[node].resize(n, -1);
        down[node].resize(n, -1);
        if (l == r) {
            for (int i = 0; i < n; i++) {
                down[node][i] = goDown(l, i);
                up[node][i] = goUp(l, i);
            }
            return;
        } 
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        for (int i = 0; i < n; i++) {
            int cur = down[node << 1][i];
            if (cur != -1) cur = down[node << 1 | 1][cur];
            down[node][i] = cur;

            cur = up[node << 1 | 1][i];
            if (cur != -1) cur = up[node << 1][cur];
            up[node][i] = cur;
        }
    }

    vector<pair<int, int>> update(int node, int l, int r, int id, int y) {
        // cout << l << ' ' << r << ' ' << id << endl;
        if (l == r) {
            vector<pair<int, int>> res;
            for (int i = y - 1; i <= y + 1; i++) {
                if (i < 0 || i >= n) continue;
                res.push_back({i, goDown(l, i)});
                res.push_back({goUp(l, i), i});
                down[node][i] = goDown(l, i);
                up[node][i] = goUp(l, i);
            }
            sort(res.begin(), res.end());
            res.resize(unique(res.begin(), res.end()) - res.begin());
            return res;
        }
        int m = l + r >> 1;
        vector<pair<int, int>> res;
        if (id <= m) {
            vector<pair<int, int>> now = update(node << 1, l, m, id, y);
            for (auto u : now) {
                int head = u.first;
                int tail = u.second;
                // down
                if (head != -1) {
                    int nextTail = tail;
                    if (nextTail != -1) nextTail = down[node << 1 | 1][nextTail];
                    down[node][head] = nextTail;
                    res.push_back({head, nextTail});
                }
                // up   
                if (tail != -1) {
                    int nextTail = down[node << 1 | 1][tail];
                    if (nextTail != -1) up[node][nextTail] = head;
                    res.push_back({head, nextTail});
                }
            }
        } else {
            vector<pair<int, int>> now = update(node << 1 | 1, m + 1, r, id, y);
            for (auto u : now) {
                int head = u.first;
                int tail = u.second;
                // down
                if (head != -1) {
                    int nextHead = up[node << 1][head];
                    if (nextHead != -1) down[node][nextHead] = tail;
                    res.push_back({nextHead, tail});
                }
                // up
                if (tail != -1) {
                    int nextHead = head;
                    if (nextHead != -1) nextHead = up[node << 1][nextHead];
                    up[node][tail] = nextHead;
                    res.push_back({nextHead, tail});
                }
            }
        }
        sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }

    int get(int u) {
        return down[1][u];
    }
} it;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n >> q;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    it.init(1, 0, m - 1);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            if (a[x][y] == '/') a[x][y] = '\\';
            else a[x][y] = '/';
            it.update(1, 0, m - 1, x, y);
        } else {
            int y;
            cin >> y;
            y--;
            int res = it.get(y);
            if (res == -1) cout << -1 << '\n';
            else cout << res + 1 << '\n';
        }
    }
    return 0;   
}