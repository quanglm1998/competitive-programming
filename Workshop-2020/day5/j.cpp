#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> l(n), w(n);
    for (int &u : l) cin >> u;
        for (int &u : w) cin >> u;

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    double res = 0;
    while (1) {
        double delta = 0, sumW = 0;
        for (int i = 0; i < n; i++) {
            int u = perm[i];
            double nextW = sumW + w[u];
            double nextDelta = (delta * sumW + (delta + 0.5 * l[u]) * w[u]) / nextW;
            cout << fixed << ' ' << setprecision(10) << delta << endl;
            cout << delta + 0.5 * l[u] << endl;
            delta = nextDelta;
            sumW = nextW;
        }
        return 0;
        res = max(res, delta);
        if (!next_permutation(perm.begin(), perm.end())) break;
    }
    cout << fixed << setprecision(10) << res << endl;
    return 0;
}