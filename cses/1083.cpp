#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    long long tot = 1ll * n * (n + 1) / 2;
    for (int i = 1; i < n; i++) {
        int u;
        cin >> u;
        tot -= u;
    }   
    cout << tot << endl;
    return 0;
}