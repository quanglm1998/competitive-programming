#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    vector<int> b(m);
    for (int &u : b) cin >> u;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int cur = 0;
    int res = 0;
    for (int u : a) {
        while (cur < b.size() && b[cur] + k < u) cur++;
        if (cur == b.size()) break;
        if (b[cur] - k <= u) {
            res++;
            cur++;
        }
    }
    cout << res << endl;
    return 0;
}