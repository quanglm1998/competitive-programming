#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &u : a) {
        cin >> u;
        u %= n;
        if (u < 0) u += n;
    }
    map<int, int> m;
    int cur = 0;
    m[0] = 1;
    long long res = 0;
    for (int i = 0; i < n; i++) {
        cur = (cur + a[i]) % n;
        res += m[cur];
        m[cur]++;
    }
    cout << res << endl;
    return 0;
}