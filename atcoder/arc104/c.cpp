#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int n;
bool f[N];
int a[N], b[N];

int check(int u, int l, int r) {
    if (u == -1) return -1;
    return u > l * 2 && u <= r * 2;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    f[0] = 1;
    set<int> has;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        if (a[i] != -1 && has.count(a[i])) {
            cout << "No\n";
            return 0;
        }
        if (b[i] != -1 && has.count(b[i])) {
            cout << "No\n";
            return 0;
        }
        has.insert(a[i]);
        has.insert(b[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (!f[j]) continue;
            bool found = 0;

            for (int k = 1; k <= n; k++) {
                int aa = check(a[k], j, i);
                int bb = check(b[k], j, i);
                // cout << i << ' ' << j << ' ' << k << ' ' << aa << ' ' << bb << '\n';
                if (aa == -1) {
                    if (bb == -1) {
                        // nothing
                    } else if (bb == 1) {
                        if (!check(b[k] - i + j, j, i) || has.count(b[k] - i + j)) {
                            found = 1;
                            break;
                        }
                    } else {
                        // nothing
                    }   
                } else if (aa == 0) {
                    if (bb == -1) {
                        // nothing
                    } else if (bb == 1) {
                        found = 1;
                        break;
                    } else {
                        // nothing
                    }
                } else {
                    if (bb == -1) {
                        if (!check(a[k] + i - j, j, i) || has.count(a[k] + i - j)) {
                            found = 1;
                            break;
                        }
                    } else if (bb == 1) {
                        if (b[k] - a[k] != i - j) {
                            found = 1;
                            break;
                        }
                    } else {
                        found = 1;
                        break;
                    }
                }
            }

            // if (found) cout << "found " << i << ' ' << j << endl;
            if (!found) {
                f[i] = 1;
                break;
            }
        }
        // cout << i << ' ' << f[i] << endl;
    }
    cout << (f[n] ? "Yes" : "No") << '\n';
    return 0;
}