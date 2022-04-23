#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    sort(a.begin(), a.end());
    int l = 0, r = a.size() - 1;
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) res[i] = a[r--];
        else res[i] = a[l++];
    }
    cout << (n - 1) / 2 << endl;
    for (int u : res) cout << u << ' ';
        cout << endl;
    return 0;
}