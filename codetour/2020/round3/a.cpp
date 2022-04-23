#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n), b(m);
    for (auto &u : a) cin >> u.first >> u.second;
        for (auto &u : b) cin >> u.first >> u.second;
    double minVal = 1e9;
    double maxVal = -1e9;
    for (auto u : a) {
        for (auto v : b) {
            double now = sqrt(1ll * (u.first - v.first) * (u.first - v.first) + 1ll * (u.second - v.second) * (u.second - v.second));
            minVal = min(minVal, now);
            maxVal = max(maxVal, now);
        }
    }
    cout << fixed << setprecision(4) << maxVal << endl << minVal << endl;
    return 0;
}