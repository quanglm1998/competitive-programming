#include <bits/stdc++.h>

using namespace std;

const int N = 500;
const int INF = (int)1e9 + 10;

int c[N][N];
vector<pair<int, int>> res;
int found = 0;

void go(int u, int v, int val) {
    if (found) return;
    if (val == 0) {
        for (auto u : res) cout << u.first << ' ' << u.second << '\n';
        found = 1;
        return;
    }   
    int id = c[u + 1][v] > c[u + 1][v + 1] ? v : v + 1;
    if (c[u][id - 1] <= val) {
        res.push_back({u + 1, id});
        go(u + 1, id, val - c[u][id - 1]);
        res.pop_back(); 
    } 
    id = id == v ? v + 1 : v;
    if (c[u][id - 1] <= val) {
        res.push_back({u + 1, id});
        go(u + 1, id, val - c[u][id - 1]);
        res.pop_back(); 
    }
}

void solve(int test) {
    cout << "Case #" << test << ":\n";
    int val;
    cin >> val;
    found = 0;
    res.clear();
    res.push_back({1, 1});
    go(1, 1, val - 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) c[i][j] = 1;
            else c[i][j] = min(INF, c[i - 1][j] + c[i - 1][j - 1]);
        }
    }
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}