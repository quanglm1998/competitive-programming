#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n;
int a[N];
int last[N];
int nxt[N];
int used[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > 0) {
            last[a[i]] = i;
        } else {
            if (!last[-a[i]]) return (cout << -1 << endl, 0);
            nxt[last[-a[i]]] = i;
        }
    }
    int mx = 0;
    vector<int> res;
    set<int> has;
    for (int i = 1; i <= n; i++) {
        if (mx < i) {
            res.push_back(i - 1);
            has.clear();
        }
        if (used[i]) continue;
        if (a[i] < 0) return (cout << -1 << endl, 0);
        if (!nxt[i]) return (cout << -1 << endl, 0);
        if (has.count(a[i])) return (cout << -1 << endl, 0);
        mx = max(mx, nxt[i]);
        used[nxt[i]] = 1;
        has.insert(a[i]);
    }
    res.push_back(n);
    cout << res.size() - 1 << '\n';
    for (int i = 1; i < res.size(); i++) cout << res[i] - res[i - 1] << ' ';
        cout << '\n';
    return 0;
}