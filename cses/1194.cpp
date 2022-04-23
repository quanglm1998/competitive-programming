#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
const int X[] = {0, -1, 0, 1};
const int Y[] = {1, 0, -1, 0};
const string patt = "RULD";

int n, m;
char s[N][N];
pair<int, int> posA;
pair<int, int> trace[N][N];
int usedA[N][N];
int usedM[N][N];

bool isInside(int u, int v) {
    return u >= 1 && u <= n && v >= 1 && v <= m;
}

bool isBoundary(int u, int v) {
    return u == 1 || u == n || v == 1 || v == m;
}

vector<pair<int, int>> traceRes(pair<int, int> u) {
    vector<pair<int, int>> res;
    while (u != posA) {
        res.push_back(u);
        u = trace[u.first][u.second];
    }
    res.push_back(u);
    reverse(res.begin(), res.end());
    return res;
}   

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'A') {
                posA = {i, j};
            }
        }
    }
    vector<pair<int, int>> lsM;
    vector<pair<int, int>> lsA;
    usedA[posA.first][posA.second] = 1;
    lsA.push_back(posA);
    if (isBoundary(posA.first, posA.second)) {
        cout << "YES\n";
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'M') {
                lsM.push_back({i, j});
                usedM[i][j] = 1;
            }
        }
    }

    while (!lsM.empty() || !lsA.empty()) {
        vector<pair<int, int>> nxtLsM;
        for (auto u : lsM) {
            for (int dir = 0; dir < 4; dir++) {
                pair<int, int> v(u.first + X[dir], u.second + Y[dir]);
                if (!isInside(v.first, v.second) || s[v.first][v.second] == '#' || usedM[v.first][v.second]) continue;
                usedM[v.first][v.second] = 1;
                nxtLsM.push_back(v);
            }
        }
        lsM.swap(nxtLsM);

        vector<pair<int, int>> nxtLsA;
        for (auto u : lsA) {
            for (int dir = 0; dir < 4; dir++) {
                pair<int, int> v(u.first + X[dir], u.second + Y[dir]);
                if (!isInside(v.first, v.second) || s[v.first][v.second] == '#' || usedM[v.first][v.second] || usedA[v.first][v.second]) continue;
                usedA[v.first][v.second] = 1;
                nxtLsA.push_back(v);
                trace[v.first][v.second] = u;
                if (isBoundary(v.first, v.second)) {
                    vector<pair<int, int>> foo = traceRes(v);
                    // for (auto u : foo) cout << u.first << ' ' << u.second << endl;
                    cout << "YES\n";
                    cout << foo.size() - 1 << '\n';
                    for (int i = 0; i + 1 < foo.size(); i++) {
                        int dir = -1;
                        for (int j = 0; j < 4; j++) {
                            if (foo[i].first + X[j] == foo[i + 1].first && foo[i].second + Y[j] == foo[i + 1].second) {
                                dir = j;
                                break;
                            }
                        }
                        assert(dir != -1);
                        cout << patt[dir];
                    }
                    cout << '\n';
                    return 0;
                }
            }
        }
        lsA.swap(nxtLsA);
    }
    cout << "NO\n";
    return 0;
}