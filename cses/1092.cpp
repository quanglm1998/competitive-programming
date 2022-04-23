#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    if (n % 4 != 0 && n % 4 != 3) {
        cout << "NO" << endl;
    }
    long long sum = 1ll * n * (n + 1) / 4;
    vector<int> res[2];
    for (int i = n; i; i--) {
        if (i <= sum) {
            sum -= i;
            res[0].push_back(i);
        } else res[1].push_back(i);
    }
    cout << "YES\n";
    for (int i = 0; i < 2; i++) {
        cout << res[i].size() << '\n';
        for (int u : res[i]) cout << u << ' ';
            cout << '\n';
    }
    return 0;
}