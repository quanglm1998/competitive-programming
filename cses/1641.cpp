#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int u, int v) {
        return a[u] < a[v];
    });
    for (int i = 0; i + 1 < n; i++) {
        int need = x - a[id[i]];
        int l = i + 1;
        int r = n - 1;
        int sum = a[id[l]] + a[id[r]];
        while (l < r) {
            if (sum == need) {
                cout << id[i] + 1 << ' ' << id[l] + 1 << ' ' << id[r] + 1 << '\n';
                return 0;
            }
            if (sum < need) {
                sum -= a[id[l++]];
                sum += a[id[l]];
            } else {
                sum -= a[id[r--]];
                sum += a[id[r]];
            }
        }
    }   
    cout << "IMPOSSIBLE\n";
    return 0;
}