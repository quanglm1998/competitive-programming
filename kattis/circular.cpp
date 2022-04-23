#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n;
vector<pair<int, char>> ls[N];
int sum[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        int u;
        cin >> c >> u;
        ls[u].push_back({i, c});
    }   
    for (int i = 0; i < N; i++) {
        if (ls[i].empty()) continue;
        vector<int> a(ls[i].size() + 1, 0);
        int minVal = 0;
        for (int j = 0; j < ls[i].size(); j++) {
            a[j + 1] = a[j] + (ls[i][j].second == 's' ? 1 : -1);
            minVal = min(minVal, a[j + 1]);
        }
        if (a.back()) continue;
        for (int j = 1; j < ls[i].size(); j++) {
            if (a[j] == minVal) {
                sum[ls[i][j - 1].first + 1]++;
                sum[ls[i][j].first + 1]--;
            }
        }
        if (a[0] == minVal) {
            sum[1]++;
            sum[ls[i][0].first + 1]--;
            sum[ls[i].back().first + 1]++;
            sum[n + 1]--;
        }
    }
    pair<int, int> res(0, -1);
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i - 1];
        res = max(res, {sum[i], -i});
    }
    cout << -res.second << ' ' << res.first << endl;
    return 0;
}