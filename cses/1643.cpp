#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    long long res = -1e18;
    long long minPref = 0;
    long long pref = 0;
    for (int u : a) {
        pref += u;
        res = max(res, pref - minPref);
        minPref = min(minPref, pref);
    }   
    cout << res << endl;
    return 0;
}