#include <bits/stdc++.h>

using namespace std;

template<typename T = int>
struct BIT {
    int n;
    vector<T> t;

    BIT(int n = 0) : n(n), t(n + 1, 0) {}

    void add(int x, T v) {
        for (; x <= n; x += x & -x) t[x] += v;
    }

    T get(int x) {
        T res = 0;
        for (; x; x -= x & -x) res += t[x];
        return res;
    }

    T get(int l, int r) {
        return get(r) - (l ? get(l - 1) : 0);
    }
};

struct Tree {
    int n;
    vector<vector<int>> adj;
    vector<int> in, out;
    vector<int> nChild;
    int cnt;
    BIT<> t;

    Tree(int n, vector<int> p) : n(n), adj(n + 1, vector<int>()), in(n + 1, 0), out(n + 1, 0), cnt(0), nChild(n + 1, 0), t(n) {
        for (int i = 2; i <= n; i++) {
            adj[p[i]].push_back(i);
        }
        dfs(1);
    }

    void dfs(int u) {   
        in[u] = ++cnt;
        nChild[u] = 1;
        for (int v : adj[u]) {
            dfs(v);
            nChild[u] += nChild[v];
        }
        out[u] = cnt;
    }

    void unite(vector<int> &u, vector<int> &v) {
        if (u.size() < v.size()) swap(u, v);
        u.insert(u.end(), v.begin(), v.end());
        v.clear();
    }

    vector<int> dfsSolve(int u, const Tree &other, vector<int> &res, int f) {
        vector<int> ls;
        int biggest = -1;
        for (int v : adj[u]) {
            if (biggest == -1 || nChild[biggest] < nChild[v]) {
                biggest = v;
            }
        }
        for (int v : adj[u]) {
            if (v == biggest) continue;
            vector<int> now = dfsSolve(v, other, res, 1);
            unite(ls, now);
        }
        vector<int> now;
        if (biggest != -1) {
            now = dfsSolve(biggest, other, res, 0);
        }
        
        for (auto v : ls) {
            t.add(other.in[v], +1);
        }

        res[u] = t.get(other.in[u], other.out[u]);

        unite(ls, now);
        if (f) {
            for (auto v : ls) {
                t.add(other.in[v], -1);
            }
        } else {
            t.add(other.in[u], +1);
        }
        ls.push_back(u);
        return ls;
    }

    vector<int> solve(const Tree &other) {
        vector<int> res(n + 1, 0);
        dfsSolve(1, other, res, 1);
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> p1(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> p1[i];
    }  
    vector<int> p2(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> p2[i];
    }
    Tree t1(n, p1);
    Tree t2(n, p2);

    vector<int> res = t1.solve(t2);
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
    cout << '\n';
    return 0;
}