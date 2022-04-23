#include <bits/stdc++.h>

using namespace std;

const int N = 50;

int r, c;
char s[N][N];
int deg[N];
int has[N];
int a[N][N];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        cin >> (s[i] + 1);
    }
    for (int i = 0; i < N; i++) memset(a[i], 0, sizeof a[i]);
    memset(deg, 0, sizeof deg);
    memset(has, 0, sizeof has);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            has[s[i][j] - 'A'] = 1;
            if (i < r && s[i][j] != s[i + 1][j]) {
                deg[s[i][j] - 'A']++;
                a[s[i + 1][j] - 'A'][s[i][j] - 'A']++;
            }
        }
    }
    queue<int> q;
    string res;
    for (int i = 0; i < N; i++) {
        if (!deg[i] && has[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res += (char)(u + 'A');
        for (int i = 0; i < N; i++) {
            if (a[u][i]) {
                deg[i] -= a[u][i];
                if (deg[i] == 0) {
                    q.push(i);
                }
            }
        }
    }
    if (*max_element(deg, deg + N) > 0) {
        cout << -1 << '\n';
        return;
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