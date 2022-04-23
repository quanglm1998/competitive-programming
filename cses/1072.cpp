#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << 1ll * i * i * (1ll * i * i - 1) / 2ll - 4ll * (i - 1) * (i - 2) << '\n';
    }   
    return 0;
}