#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    map<long long, int> m;
    long long cur = 0;
    m[0] = 1;
    long long res = 0;
    for (int u : a) {
        cur += u;
        if (m.count(cur - x)) res += m[cur - x];
        m[cur]++;
    }   
    cout << res << endl;
    return 0;
}