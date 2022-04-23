#include <bits/stdc++.h>

using namespace std;

const int N = 110;

struct Data {
    int x, y, u, v;
    Data(int x = 0, int y = 0, int u = 0, int v = 0) : x(x), y(y), u(u), v(v) {}
};

int n;
pair<int, int> a[N];
int deg[N];
vector<int> nxt[N];
int len[N];

bool isUpper(pair<int, int> u) {
    return u.second > 0 || (u.second == 0 && u.first > 0);
}

long long cross(pair<int, int> u, pair<int, int> v) {
    return 1ll * u.first * v.second - 1ll * v.first * u.second;
}

bool smaller(pair<int, int> u, pair<int, int> v) {
    if (isUpper(u) != isUpper(v)) return isUpper(u);
    return cross(u, v) > 0;
}

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<Data> ls;
    ls.reserve(n * n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j != i) {
                ls.push_back(Data(a[j].first - a[i].first, a[j].second - a[i].second, i, j));
            }
        }
    }
    sort(ls.begin(), ls.end(), [&](Data &u, Data &v) {
        return smaller(make_pair(u.x, u.y), make_pair(v.x, v.y));
    });
    
    int res = 1;

    for (int l = 0, r = 0; l < ls.size(); l = r) {
        while (r < ls.size() && !smaller(make_pair(ls[l].x, ls[l].y), make_pair(ls[r].x, ls[r].y))) r++;

        fill(deg + 1, deg + n + 1, 0);
        for (int i = 1; i <= n; i++) nxt[i].clear();
        fill(len + 1, len + n + 1, 1);
        for (int i = l; i < r; i++) {
            deg[ls[i].v]++;
            nxt[ls[i].u].push_back(ls[i].v);
            // cout << ls[i].u << ' ' << ls[i].v << endl;
        }   
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) q.push(i);
        }
        int tot = 0;
        int odd = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (nxt[u].empty()) {
                if (len[u] >= 2) {
                    tot += len[u];
                    if (len[u] & 1) odd ^= 1;
                }
            } else {
                for (int v : nxt[u]) {
                    deg[v]--;
                    if (deg[v] == 0) {
                        q.push(v);
                        len[v] = len[u] + 1;
                    }
                }
            }
        }
        // cout << l << ' ' << r << ' ' << tot << ' ' << odd << endl;
        if (!odd)  res = max(res, min(n, tot + 2));
        else res = max(res, min(n, tot + 1));
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}