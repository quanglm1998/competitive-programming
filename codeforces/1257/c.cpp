#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        int res = N;
        map<int, int> last;
        for (int i = 1; i <= n; i++) {
            int u;
            cin >> u;
            if (last.count(u)) {
                res = min(res, i - last[u] + 1);
            }
            last[u] = i;
        }
        if (res == N) cout << -1 << '\n';
        else cout << res << '\n';
    }    
    return 0;
}