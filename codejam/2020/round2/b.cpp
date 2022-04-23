#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
const int INF = 1e9;

int n, m;
int a[N];
pair<int, int> edges[N];
vector<int> adj[N];
int res[N];
int ackTime[N];

void solve(int u, int t) {
    for (int id : adj[u]) {
        if (res[id]) continue;
        int v = edges[id].first == u ? edges[id].second : edges[id].first;
        if (ackTime[v] < INF) res[id] = max(1, t - ackTime[v]);
    }
    ackTime[u] = t;
}

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        ackTime[i] = INF;
    }
    ackTime[1] = 0;

    fill(res + 1, res + m + 1, 0);


    for (int i = 1; i <= m; i++) {
        cin >> edges[i].first >> edges[i].second;
        adj[edges[i].first].push_back(i);
        adj[edges[i].second].push_back(i);
    }

    vector<pair<int, int>> knownLen;
    map<int, vector<int>> notKnownLen;
    for (int i = 2; i <= n; i++) {
        if (a[i] < 0) {
            notKnownLen[-a[i]].push_back(i);
        } else {
            knownLen.push_back({i, a[i]});
        }
    }

    int curId = 0;
    int curACK = 1;
    int last = 0;
    for (auto ack : notKnownLen) {
        while (curACK < ack.first) {
            assert(curId < knownLen.size());
            solve(knownLen[curId].first, knownLen[curId].second);
            last = knownLen[curId].second;

            curACK++;
            curId++;
        }

        for (auto u : ack.second) solve(u, last + 1);

        last++;

        curACK += ack.second.size();
    }

    while (curId < knownLen.size()) {
        solve(knownLen[curId].first, knownLen[curId].second);
        curId++;
    }

    for (int i = 1; i <= m; i++) cout << max(1, res[i]) << ' ';
        cout << '\n';
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