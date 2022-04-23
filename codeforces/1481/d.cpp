#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n, m;
char a[N][N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> (a[i] + 1);
        }
        pair<int, int> same(-1, -1);
        for (int i = 1; i <= n && same.first == -1; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (a[i][j] == a[j][i]) {
                    same = {i, j};
                    break;
                }
            }
        }
        if (m == 1) {
            cout << "YES\n";
            cout << 1 << ' ' << 2 << '\n';
            continue;
        }
        if (same.first != -1) {
            cout << "YES\n";
            for (int i = 1; i <= m + 1; i++) {
                if (i & 1) cout << same.first << ' ';
                else cout << same.second << ' ';
            }
            cout << '\n';
            continue;
        }
        if (n == 2) {
            if (m % 2 == 0) {
                cout << "NO\n";
                continue;
            }
            cout << "YES\n";
            for (int i = 1; i <= m + 1; i++) {
                cout << (i % 2) + 1 << ' ';
            }
            cout << '\n';
            continue;
        }
        
        auto get = [](int u) {
            u++;
            if (u > 3) return 1;
            return u;
        };

        int cir = 1;
        for (int i = 2; i <= 3; i++) {
            if (a[i][get(i)] != a[1][2]) cir = 0;
        }
        if (cir == 1) {
            cout << "YES\n";
            for (int i = 1; i <= m + 1; i++) {
                cout << (i % 3) + 1 << ' ';
            }
            cout << '\n';
            continue;
        }

        int pos = 0;
        for (int i = 1; i <= 3; i++) {
            int nxt = get(i);
            int nxt2 = get(nxt);
            if (a[i][nxt] == a[nxt][nxt2]) {
                pos = i;
            }
        }

        assert(pos != 0);
        int u = pos;
        int v = get(u);
        int w = get(v);
        deque<int> res;
        if (m % 2 == 0) {
            if (m == 2) {
                cout << "YES\n";
                cout << u << ' ' << v << ' ' << w << '\n';
                continue;
            }
            m -= 4;
            res.push_back(v);
            res.push_back(w);
            res.push_back(v);
            res.push_back(u);
            res.push_back(v);
            int cur = v;
            while (m > 0) {
                m -= 2;
                if (cur == v) {
                    res.push_front(u);
                    res.push_back(w);
                    cur = 0;
                } else {    
                    res.push_back(v);
                    res.push_front(v);
                    cur = v;
                }
            }
        } else {
            m -= 3;
            res.push_back(v);
            res.push_back(w);
            res.push_back(u);
            res.push_back(v);
            int cur = v;
            while (m > 0) {
                m -= 2;
                if (cur == v) {
                    res.push_front(u);
                    res.push_back(w);
                    cur = 0;
                } else {    
                    res.push_back(v);
                    res.push_front(v);
                    cur = v;
                }
            }
        }   
        cout << "YES\n";
        for (int u : res) {
            cout << u << ' ';
        }
        cout << '\n';
        string foo = "";
        for (int i = 0; i + 1 < res.size(); i++) {
            foo += a[res[i]][res[i + 1]];
        }

        auto isPal = [](const string &s) {
            for (int i = 0; i < s.size(); i++) {
                if (s[i] != s[s.size() - i - 1]) return false;
            }
            return true;
        };

        assert(isPal(foo));
    }
    return 0;
}