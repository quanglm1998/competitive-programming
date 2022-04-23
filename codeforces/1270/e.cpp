#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n;
pair<int, int> a[N];
map<pair<int, int>, int> m;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;   
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    if (n == 2) {
        cout << 1 << endl;
        cout << 1 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                pair<int, int> foo(a[i].first - a[j].first, a[i].second - a[j].second);
                m[foo]++;
            }
        }
    }
    pair<int, int> res(0, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                pair<int, int> foo(a[i].first - a[j].first, a[i].second - a[j].second);
                if (m[foo] == 1) {
                    res = {i, j};
                }
            }
        }
    }
    cout << 2 << endl;
    cout << res.first << ' ' << res.second << endl;
    return 0;
}