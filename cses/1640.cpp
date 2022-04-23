#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, x;
    cin >> n >> x;
    map<int, int> m;
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        if (m.count(x - u)) {
            cout << m[x - u] << ' ' << i << endl;
            return 0;
        }
        m[u] = i;
    }   
    cout << "IMPOSSIBLE\n" << endl;
    return 0;
}