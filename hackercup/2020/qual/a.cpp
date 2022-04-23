#include <bits/stdc++.h>

using namespace std;

const int N = 55;

int n;
char in[N], out[N];

void solve(int test) {
    cout << "Case #" << test << ":\n";
    cin >> n;
    cin >> (in + 1);
    cin >> (out + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                cout << 'Y';
                continue;
            }
            if (i < j) {
                int found = 0;
                for (int k = i; k < j; k++) {
                    if (out[k] == 'N') found = 1;
                }
                for (int k = i + 1; k <= j; k++) {
                    if (in[k] == 'N') found = 1;
                }
                cout << (found ? 'N' : 'Y');
            } else {
                int found = 0;
                for (int k = j + 1; k <= i; k++) {
                    if (out[k] == 'N') found = 1;
                }
                for (int k = j; k < i; k++) {
                    if (in[k] == 'N') found = 1;
                }
                cout << (found ? 'N' : 'Y');
            }
        }
        cout << '\n';
    }
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