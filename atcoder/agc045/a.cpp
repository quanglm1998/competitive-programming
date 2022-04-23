#include <bits/stdc++.h>

using namespace std;

const int N = 210;
const int LOG = 63;

int n;
long long a[N];
char s[N];
long long basis[LOG];

void add(long long u) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (u >> i & 1) {
            if (!basis[i]) {
                basis[i] = u;
                return;
            }
            u ^= basis[i];
        }
    }
}

bool check(long long u) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (u >> i & 1) {
            if (!basis[i]) {
                return 0;
            }
            u ^= basis[i];
        }
    }
    return u == 0;
}

void solve(int test) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> (s + 1);
    for (int i = 0; i < LOG; i++) {
        basis[i] = 0;
    }

    for (int i = n; i; i--) {
        if (s[i] == '0') {
            add(a[i]);
        } else {
            if (!check(a[i])) {
                cout << 1 << '\n';
                return;
            }
        }
    }
    cout << 0 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}