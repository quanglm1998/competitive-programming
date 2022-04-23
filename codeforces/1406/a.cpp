#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        map<int, int> has;
        for (int i = 1; i <= n; i++) {
            int u; cin >> u;
            has[u]++;
        }
        int num = 2;
        int res = 0;
        for (int i = 0; i < 100 && num > 0; i++) {
            if (has[i] >= num) continue;
            res += (num - has[i]) * i;   
            num = has[i];
        }
        cout << res << endl;
    }
    return 0;
}