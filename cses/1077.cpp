#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    multiset<int> s[2];
    long long sum[2] = {0, 0};
    for (int i = 0; i < n; i++) {
        // insert
        if (s[0].empty() || *s[0].rbegin() < a[i]) {
            s[1].insert(a[i]);
            sum[1] += a[i];
        } else {
            s[0].insert(a[i]);
            sum[0] += a[i];
        }
        // delete
        if (i >= k) {
            if (s[0].find(a[i - k]) != s[0].end()) {
                s[0].erase(s[0].find(a[i - k]));
                sum[0] -= a[i - k];
            } else {
                s[1].erase(s[1].find(a[i - k]));
                sum[1] -= a[i - k];
            }
        }
        // balance
        while (s[0].size() > s[1].size() + 1) {
            int u = *s[0].rbegin();
            s[0].erase(s[0].find(u));
            sum[0] -= u;
            s[1].insert(u);
            sum[1] += u;
        }
        while (s[1].size() > s[0].size()) {
            int u = *s[1].begin();
            s[1].erase(s[1].find(u));
            sum[1] -= u;
            s[0].insert(u);
            sum[0] += u;   
        }
        if (i >= k - 1) {
            int median = *s[0].rbegin();
            cout << 1ll * median * s[0].size() - sum[0] + sum[1] - 1ll * median * s[1].size() << ' ';
        }

    }
    cout << '\n';
    return 0;
}