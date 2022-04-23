#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    sort(a.begin(), a.end());
    cout << max(accumulate(a.begin(), a.end(), 0ll), 2ll * a.back()) << endl;   
    return 0;
}