#include <bits/stdc++.h>

using namespace std;

/**
 * minimize c^T * x
 * subject to Ax <= b
 * and x >= 0
 * The input matrix a will have the following form
 * 0 c c c c c
 * b A A A A A
 * b A A A A A
 * b A A A A A
 * Result vector will be: val x x x x x
 **/

typedef long double ld;
const ld EPS = 1e-4;
struct LPSolver {
    static vector<ld> simplex(vector<vector<ld>> a) {
        int n = (int) a.size() - 1;
        int m = (int) a[0].size() - 1;
        vector<int> left(n + 1);
        vector<int> up(m + 1);
        iota(left.begin(), left.end(), m);
        iota(up.begin(), up.end(), 0);
        auto pivot = [&](int x, int y) {
            swap(left[x], up[y]);
            ld k = a[x][y];
            a[x][y] = 1;
            vector<int> pos;
            for (int j = 0; j <= m; j++) {
                a[x][j] /= k;
                if (fabs(a[x][j]) > EPS) pos.push_back(j);
            }
            for (int i = 0; i <= n; i++) {
                if (fabs(a[i][y]) < EPS || i == x) continue;
                k = a[i][y];
                a[i][y] = 0;
                for (int j : pos) a[i][j] -= k * a[x][j];
            }
        };
        while (1) {
            int x = -1;
            for (int i = 1; i <= n; i++) {
                if (a[i][0] < -EPS && (x == -1 || a[i][0] < a[x][0])) {
                    x = i;
                }
            }
            if (x == -1) break;
            int y = -1;
                for (int j = 1; j <= m; j++) {
                    if (a[x][j] < -EPS && (y == -1 || a[x][j] < a[x][y])) {
                    y = j;
                }
            }
            if (y == -1) return vector<ld>(); // infeasible
            pivot(x, y);
        }
        while (1) {
            int y = -1;
            for (int j = 1; j <= m; j++) {
                if (a[0][j] > EPS && (y == -1 || a[0][j] > a[0][y])) {
                    y = j;
                }
            }
            if (y == -1) break;
            int x = -1;
            for (int i = 1; i <= n; i++) {
                if (a[i][y] > EPS && (x == -1 || a[i][0] / a[i][y] < a[x][0] / a[x][y])) {
                    x = i;
                }
            }
            if (x == -1) return vector<ld>(); // unbounded
            pivot(x, y);
        }
        vector<ld> ans(m + 1);
        for (int i = 1; i <= n; i++) {
            if (left[i] <= m) ans[left[i]] = a[i][0];
        }
        ans[0] = -a[0][0];
        return ans;
    }
};

const int N = 110;

int n;
int numBit[N];
int b[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<vector<ld>> a;
    vector<ld> firstRow(31);
    firstRow[0] = 0;
    for (int i = 1; i <= 30; i++) {
        firstRow[i] = (1 << 30 - i);
    }
    a.push_back(firstRow);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        b[i] = u;
        numBit[i] = __builtin_popcount(u);
        vector<ld> pos(31), neg(31);
        for (int j = 0; j < 30; j++) {
            if (u >> j & 1) pos[j + 1] = -1;
            else pos[j + 1] = 1;
            neg[j + 1] = -pos[j + 1];
        }
        a.push_back(pos);
        a.push_back(neg);
    }
    int diff=  0;
    for (int i = 2; i <= n; i++) {
        if (abs(numBit[i] - numBit[i - 1]) % 2) {
            cout << -1 << endl;
            return 0;
        }
        diff |= (numBit[i] != numBit[i - 1]);
    }
    if (!diff) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < 30; i++) {
        vector<ld> now(31, 0);
        now[i + 1] = 1;
        now[0] = 1;
        a.push_back(now);
        now[i + 1] = -1;
        now[0] = 0;
        a.push_back(now);
    }
    for (int num = 0; num <= 30; num++) {
        for (int i = 1; i <= n; i++) {
            int delta = num - numBit[i];
            a[i * 2 - 1][0] = delta;
            a[i * 2][0] = -delta;
        }
        vector<ld> res = LPSolver::simplex(a);
        if (res.size() == 0) continue;
        int found = 0;
        for (int i = 1; i < res.size(); i++) {
            if (abs(res[i]) > EPS && abs(res[i] - 1) > EPS) {
                found = 1;
                break;
            }
        }
        if (found) continue;
        int ans = 0;
        for (int i = 0; i < 30; i++) {
            if (res[i + 1] > 0.5) ans |= (1 << i);
        }
        cout << ans << endl;
        return 0;
    }
    cout << -1 << endl;
    return 0;
}