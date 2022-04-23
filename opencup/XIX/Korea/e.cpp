#include <bits/stdc++.h>

using namespace std;

const int N = 300010;

int n, m;
set<pair<int, int>> edges;
set<pair<int, int>> degNode;
set<int> adj[N];

void addEdge(int u, int v) {
    if (u > v) swap(u, v);
    if (edges.count({u, v})) return;
    degNode.erase({adj[u].size(), u});
    degNode.erase({adj[v].size(), v});
    adj[u].insert(v);
    adj[v].insert(u);
    edges.insert({u, v});
    degNode.insert({adj[u].size(), u});
    degNode.insert({adj[v].size(), v});
}

void removeEdge(int u, int v) {
    if (u > v) swap(u, v);
    assert(edges.count({u, v}));
    degNode.erase({adj[u].size(), u});
    degNode.erase({adj[v].size(), v});
    adj[u].erase(v);
    adj[v].erase(u);
    edges.erase({u, v});
    if (!adj[u].empty()) degNode.insert({adj[u].size(), u});
    if (!adj[v].empty()) degNode.insert({adj[v].size(), v});
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }
    while (degNode.size() > 2) {
        auto it = degNode.begin();
        for (int i = 0; i < 2; i++) {
            if (it->first == 1) {
                it++;
            } else break;
        }
        if (it->first != 2) {
            cout << "No\n";
            return 0;
        }
        int u = it->second;
        vector<int> ls;
        for (int v : adj[u]) ls.push_back(v);
        assert(ls.size() == 2);
        for (int v : ls) removeEdge(u, v);
        addEdge(ls[0], ls[1]);
    }
    cout << "Yes\n";
    return 0;
}