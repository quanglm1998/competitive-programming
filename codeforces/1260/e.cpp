#include <bits/stdc++.h>

using namespace std;

const int N = 1000000;

int n;
int a[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    multiset<int> s;
    long long res = 0;
    s.insert(a[n]);
    int lg = round(log2(n));
    int last = n - 1;
    for (int i = lg - 1; i >= 0; i--) {
        if (s.count(-1)) {
            cout << res << endl;
            return 0;
        }
        res += *s.begin();
        s.erase(s.begin());
        for (int j = 0; j < (1 << i); j++) {
            s.insert(a[last--]);
        }
    }
    cout << res << endl;
    return 0;
}