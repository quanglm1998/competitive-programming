#include <bits/stdc++.h>

using namespace std;



void solve(int test) {
    cout << "Case #" << test << ": ";
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &u : a) cin >> u;
    int cur = 2;
    int last = a[1] - a[0];
    int res = 2;
    for (int i = 2; i < a.size(); i++) {
        if (a[i] - a[i - 1] == last) {
            cur++;
        } else {
            cur = 2;
            last = a[i] - a[i - 1];
        }
        res = max(res, cur);
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