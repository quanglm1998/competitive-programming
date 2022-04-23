#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n, m;
char s[N][N];
vector<int> ls[N];
int last[N];
pair<int, int> res[N][N];
int ans[N][N];

void add(int x, int y, int delta) {
    // if (x < 1 || x > n || y < 1 || y > m) {
    //     cout << "FAIL " << x << ' ' << y << endl;
    //     cout << n << ' ' << m << endl;
    //     exit(1);
    // }
    res[x][y].first += delta;
    res[x][y].second += delta;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
    }
    for (int j = 1; j <= m; j++) {
        last[j] = 1;
    }
    for (int lower = 1; lower <= n; lower++) {
        for (int i = 1; i <= lower; i++) {
            ls[i].clear();
        }
        for (int j = 1; j <= m; j++) {
            if (s[lower][j] != '.') last[j] = lower + 1;
            if (last[j] <= lower) {
                ls[last[j]].push_back(j);
            }
        }
        // cout << "# " << lower << endl;
        // for (int j = 1; j <= m; j++) {
        //     cout << last[j] << ' ';
        // }
        // cout << endl;

        set<pair<int, int>> s;
        for (int i = 1; i <= lower; i++) {
            for (int u : ls[i]) {
                pair<int, int> now(u, u);
                add(lower - i + 1, 1, 1);
                auto it = s.lower_bound(now);
                if (it != s.end() && it->first == now.second + 1) {
                    add(lower - i + 1, now.second - now.first + 1, -1);
                    add(lower - i + 1, it->second - it->first + 1, -1);
                    now.second = it->second;
                    add(lower - i + 1, now.second - now.first + 1, 1);
                    s.erase(it);
                }
                it = s.lower_bound(now);
                if (it != s.begin()) {
                    it--;
                    if (it->second == now.first - 1) {
                        add(lower - i + 1, now.second - now.first + 1, -1);
                        add(lower - i + 1, it->second - it->first + 1, -1);
                        now.first = it->first;
                        add(lower - i + 1, now.second - now.first + 1, 1);       
                        s.erase(it);
                    }
                }
                s.insert(now);
            }
        }
        // cout << s.size() << endl;
    }   
    for (int i = n; i; i--) {
        for (int j = m; j; j--) {
            if (i < n) ans[i][j] += ans[i + 1][j];
            if (j < m) {
                res[i][j].first += res[i][j + 1].first + res[i][j + 1].second;
                res[i][j].second += res[i][j + 1].second;
            }
            ans[i][j] += res[i][j].first;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}