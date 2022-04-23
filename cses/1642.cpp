#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    long long x;
    cin >> n >> x;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    map<long long, pair<int, int>> m;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long need = x - a[i] - a[j];
            if (m.count(need)) {
                cout << i + 1 << ' ' << j + 1 << ' ' << m[need].first + 1 << ' ' << m[need].second + 1 << '\n';
                return 0;
            }
        }
        for (int j = 0; j < i; j++) {
            m[a[i] + a[j]] = {i, j};
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}