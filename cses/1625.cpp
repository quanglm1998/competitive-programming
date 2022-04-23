#include <bits/stdc++.h>

using namespace std;

const int N = 7;
const int X[] = {0, -1, 0, 1};
const int Y[] = {1, 0, -1, 0};
const string patt = "RULD";

char s[48];
int res = 0;
bool used[N][N];

inline bool isInside(int u, int v) {
    return u >= 0 && u < N && v >= 0 && v < N;
}

bool freeCell(int u, int v) {
    return isInside(u, v) && !used[u][v];
}

void solve(int u, int v, int id) {
    if (id == 48) {
        res += (u == N - 1 && v == 0);
        return;
    }
    used[u][v] = 1;
    if (freeCell(u + 1, v) && freeCell(u - 1, v) && !freeCell(u, v + 1) && !freeCell(u, v - 1)) {
        used[u][v] = 0;
        return;
    }
    if (!freeCell(u + 1, v) && !freeCell(u - 1, v) && freeCell(u, v + 1) && freeCell(u, v - 1)) {
        used[u][v] = 0;
        return;
    }
    if (s[id] == '?') {
        for (int i = 0; i < 4; i++) {
            int uu = u + X[i];
            int vv = v + Y[i];
            if (isInside(uu, vv) && !used[uu][vv] && (id == 47 || uu != N - 1 || vv != 0)) {
                solve(uu, vv, id + 1);
            }
        }
    } else {
        int dir = patt.find(s[id]);
        int uu = u + X[dir];
        int vv = v + Y[dir];
        if (isInside(uu, vv) && !used[uu][vv] && (id == 47 || uu != N - 1 || vv != 0)) {
            solve(uu, vv, id + 1);
        }
    }
    used[u][v] = 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s;
    solve(0, 0, 0);
    cout << res << '\n';
    return 0;
}