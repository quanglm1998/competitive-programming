#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
vector<int> adj[N];

vector<int> dfs(int u) {
    vector<int> res = {1};
    for (int v : adj[u]) {
        vector<int> now = dfs(v);

        while (!now.empty() && now.back() < res.back()) now.pop_back();

        vector<int> foo(res.size() + now.size());
        merge(now.begin(), now.end(), res.begin(), res.end(), foo.begin(), [&](int u, int v) {return u > v;});
        // cout << "# " << u << ' ' << v << endl;
        // for (auto u : foo) cout << u << ' ';
        //     cout << endl;
        res.clear();
        for (int u : foo) {
            res.push_back(u);
            while (res.size() > 1 && res.back() == res[res.size() - 2]) {
                int bar = res.back();
                res.pop_back();
                res.pop_back();
                res.push_back(bar + 1);
            }
        }
        // for (auto u : res) cout << u << ' ';
        // cout << endl;
    }
    // cout << "# " << u << endl;
    // for (auto u : res) cout << u << ' ';
    //     cout << endl;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int u;
        cin >> u;
        adj[u + 1].push_back(i);
    }
    vector<int> res = dfs(1);
    cout << res[0] << endl;
    return 0;
}