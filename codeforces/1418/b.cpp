#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n + 1, 0);
        for (int i = 1; i <= n; i++) cin >> a[i];
        vector<int> l(n + 1, 0);
        for (int i = 1; i <= n; i++) cin >> l[i];
        vector<int> ls;
        for (int i = 1; i <= n; i++) if (l[i] == 0) ls.push_back(a[i]);
        sort(ls.rbegin(), ls.rend());
        int res = 0;
        int sum = 0;
        int cur = 0;
        for (int i = 1; i <= n; i++) {
            if (!l[i]) a[i] = ls[cur++];
            sum += a[i];
            if (sum < 0) res = i;
        }
        for (int i = 1; i <= n; i++) cout << a[i] << ' ';
            cout << endl;
    }
    return 0;
}