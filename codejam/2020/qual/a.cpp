#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int n;
int a[N][N];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    int k = 0;
    for (int i = 1; i <= n; i++) k += a[i][i];
    int row = 0;
    for (int i = 1; i <= n; i++) {
        set<int> s;
        int f = 0;
        for (int j = 1; j <= n; j++) {
            if (s.count(a[i][j])) {
                f = 1;
                break;
            }
            s.insert(a[i][j]);
        }
        row += f;
    }

    int col = 0;
    for (int j = 1; j <= n; j++) {
        set<int> s;
        int f = 0;
        for (int i = 1; i <= n; i++) {
            if (s.count(a[i][j])) {
                f = 1;
                break;
            }
            s.insert(a[i][j]);
        }
        col += f;
    }
    cout << k << ' ' << row << ' ' << col << '\n';
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