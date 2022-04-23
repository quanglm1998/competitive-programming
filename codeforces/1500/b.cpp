#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1000010;

int n, m, k, g;
vector<int> a, b;
vector<pair<int, int>> ls[N];

int getVal(int mod, int val, int l, int r) {
    if (l > r) return 0ll;
    int ll = lower_bound(ls[val].begin(), ls[val].end(), make_pair(mod, l)) - ls[val].begin() - 1;
    int rr = upper_bound(ls[val].begin(), ls[val].end(), make_pair(mod, r)) - ls[val].begin() - 1;
    return (r - l + n) / n - (rr - ll);
}

int get(int u) {
    int v = u / (n * m / g);
    u %= (n * m / g);
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += v * getVal(i % g, a[i], 0, n * m / g - 1);
        res += getVal(i % g, a[i], i, u);
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    a.resize(n);
    b.resize(m);
    for (int &u : a) {
        cin >> u;
    }
    for (int &u : b) {
        cin >> u;
    }
    if (n > m) {
        swap(n, m);
        swap(a, b);
    }
    g = __gcd(n, m);
    
    for (int i = 0; i < n * m / g; i++) {
        ls[b[i % m]].push_back({i % g, i});
    }
    for (int i = 0; i < N; i++) {
        sort(ls[i].begin(), ls[i].end());
    }



    int low = 0, high = 1e18;
    while (high - low > 1) {
        int mid = low + high >> 1;
        int foo = get(mid);
        if (foo > k) high = mid;
        else low = mid;
    }
    cout << low + 1 << '\n';
    return 0;
}