#include <bits/stdc++.h>

using namespace std;

const int N = 5010;

int g[N];
bool has[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    g[0] = g[1] = 0;
    for (int i = 2; i < N; i++) {
        fill(has, has + N, 0);
        for (int j = 0; j + 2 <= i; j++) {
            has[g[j] ^ g[i - j - 2]] = 1;
        }
        g[i] = 0;
        while (has[g[i]]) g[i]++;
    }

    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        cout << (g[n] ? "First" : "Second") << '\n';
    }
    return 0;
}