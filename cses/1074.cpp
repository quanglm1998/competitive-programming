#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    sort(a.begin(), a.end());
    long long res = 0;
    for (int u : a) {
        res += abs(u - a[a.size() / 2]);
    }   
    cout << res << endl;
    return 0;
}